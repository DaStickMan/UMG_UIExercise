// Fill out your copyright notice in the Description page of Project Settings.


#include "FriendsListController.h"

#include "Components/VerticalBoxSlot.h"
#include "Kismet/KismetMathLibrary.h"


void UFriendsListController::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	DataManager = NewObject<UFriendsDataManager>();
	DataManager->OnDataChanged.AddDynamic(this, &UFriendsListController::HandleDataChanged);

	if(OnlineFriendsButton && OfflineFriendsButton)
	{
		OnlineFriendsButton->OnClicked.AddDynamic(this, &UFriendsListController::OnOnlineFriendsButtonClicked);
		OfflineFriendsButton->OnClicked.AddDynamic(this, &UFriendsListController::OnOfflineFriendsButtonClicked);
	}
	
	TArray<FFriendsListData*> FriendsData = DataManager->LoadDataTable(Friends.DataTable.Get());
	
	for (const auto Friend: FriendsData)
	{
		AddFriend(*Friend);
	}

	StartRandomStatusUpdates();
}

void UFriendsListController::AddFriend(const FFriendsListData& Friend)
{
	if (OnlineVerticalBox && OfflineVerticalBox && FriendRowWidgetClass)
	{
		// Create an instance of the FriendRowWidget blueprint
		UFriendRowWidget* NewFriendRow = CreateWidget<UFriendRowWidget>(this, FriendRowWidgetClass);

		// Set the data for the new friend row
		NewFriendRow->SetFriendData(Friend.NickName.ToString(), FString::Printf(TEXT("%lld"), Friend.Level), Friend.IsConnected);

		UVerticalBoxSlot* NewSlot;
		
		if(Friend.IsConnected)
		{
			NewSlot = OnlineVerticalBox->AddChildToVerticalBox(NewFriendRow);
		}
		else
		{
			NewSlot = OfflineVerticalBox->AddChildToVerticalBox(NewFriendRow);
		}

		if (NewSlot)
		{
			NewSlot->SetPadding(FMargin(0, 50.0f, 0, 50.0f)); // Set the padding as needed
		}

		FriendsWidgetMap.Add(Friend.NickName.ToString(), NewFriendRow);
	}
}

void UFriendsListController::HandleDataChanged(FriendsDataManagerOperationType type, FFriendsListData friendData)
{
	switch (type)
	{
		case FriendsDataManagerOperationType::Update:
			UpdateStatus(friendData);
			break;
		default: ;
	}
}

void UFriendsListController::OnOnlineFriendsButtonClicked()
{
	if(OnlineVerticalBox)
	{
		const ESlateVisibility visibility = OnlineVerticalBox->GetParent()->GetVisibility() == ESlateVisibility::Visible ?
			ESlateVisibility::Collapsed : ESlateVisibility::Visible;

		OnlineVerticalBox->GetParent()->SetVisibility(visibility);
	}	
}

void UFriendsListController::OnOfflineFriendsButtonClicked()
{
	if(OfflineVerticalBox)
	{
		const ESlateVisibility visibility = OfflineVerticalBox->GetParent()->GetVisibility() == ESlateVisibility::Visible ?
			ESlateVisibility::Collapsed : ESlateVisibility::Visible;

		OfflineVerticalBox->GetParent()->SetVisibility(visibility);		
	}
}

void UFriendsListController::StartRandomStatusUpdates()
{
	// Set a random timer to call RandomlyChangePlayerStatus
	float RandomDelay = UKismetMathLibrary::RandomFloatInRange(2.0f, 5.0f); // Random time between 2 to 5 seconds
	FTimerHandle RandomStatusTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(RandomStatusTimerHandle, this, &UFriendsListController::RandomlyChangePlayerStatus, RandomDelay, true);
}

void UFriendsListController::RandomlyChangePlayerStatus()
{
	// Check if there are any players in the FriendsData array
	if (FriendsWidgetMap.Num() == 0)
	{
		return; // No players to change status
	}
	
	// Select a random index
	int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, FriendsWidgetMap.Num() - 1);	
	const FText nickName = FText::FromString(GetFriendNickNameByPosition(RandomIndex));
    DataManager->UpdateStatus(nickName);
}

void UFriendsListController::DisplayToast(const FText& Message)
{
	if (ToastPopupWidgetClass) // Assuming this is the UToastPopupWidget class set in the editor
	{
		UToastPopupWidget* ToastPopup = CreateWidget<UToastPopupWidget>(GetWorld(), ToastPopupWidgetClass);
		if (ToastPopup)
		{
			ToastPopup->AddToViewport();
			ToastPopup->ShowToast(Message, 3.0f); // Show for 3 seconds
		}
	}
}

FString UFriendsListController::GetFriendNickNameByPosition(int32 Index)
{
	// Get the keys and values from the TMap
	TArray<FString> Keys;
	FriendsWidgetMap.GetKeys(Keys);

	// Check if the index is valid
	if (Index >= 0 && Index < Keys.Num())
	{
		// Get the key at the specified index
		FString Key = Keys[Index];

		return Key;
	}

	return ""; // Return nullptr if the index is invalid or the widget is not found
}

void UFriendsListController::UpdateStatus(const FFriendsListData& friendData)
{	
	FString NickNameString = friendData.NickName.ToString();
	UFriendRowWidget** FriendRow = FriendsWidgetMap.Find(NickNameString);

	if(FriendRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Nickname: %s, Status: %s"), *NickNameString, friendData.IsConnected ? TEXT("Connected") : TEXT("Disconnected"));

		if(friendData.IsConnected)
		{
			DisplayToast(FText::FromString(NickNameString));
			if(OfflineVerticalBox->HasChild(*FriendRow))
			{
				OfflineVerticalBox->RemoveChild(*FriendRow);
			}
		}
		else
		{
			if(OnlineVerticalBox->HasChild(*FriendRow))
			{
				OnlineVerticalBox->RemoveChild(*FriendRow);
			}
		}
		
		FriendsWidgetMap.Remove(NickNameString);
		
		AddFriend(friendData);
	}
}
