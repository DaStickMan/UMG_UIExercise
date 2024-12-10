// Fill out your copyright notice in the Description page of Project Settings.


#include "FriendsListController.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"


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
		AddFriend(Friend);
	}
}

void UFriendsListController::AddFriend(const FFriendsListData* Friend)
{
	if (OnlineVerticalBox && OfflineVerticalBox && Friend && FriendRowWidgetClass)
	{
		// Create an instance of the FriendRowWidget blueprint
		UFriendRowWidget* NewFriendRow = CreateWidget<UFriendRowWidget>(this, FriendRowWidgetClass);

		// Set the data for the new friend row
		NewFriendRow->SetFriendData(Friend->NickName.ToString(), FString::Printf(TEXT("%lld"), Friend->Level), Friend->IsConnected);

		if(Friend->IsConnected)
		{
			if (UVerticalBoxSlot* NewSlot = OnlineVerticalBox->AddChildToVerticalBox(NewFriendRow))
			{
				NewSlot->SetPadding(FMargin(0, 50.0f, 0, 50.0f)); // Set the padding as needed
			}
		}
		else
		{
			if (UVerticalBoxSlot* NewSlot = OfflineVerticalBox->AddChildToVerticalBox(NewFriendRow))
			{
				NewSlot->SetPadding(FMargin(0, 50.0f, 0, 50.0f)); // Set the padding as needed
			}
		}
	}
}

void UFriendsListController::HandleDataChanged()
{	
}

void UFriendsListController::OnOnlineFriendsButtonClicked() const
{
	if(OnlineVerticalBox)
	{
		const ESlateVisibility visibility = OnlineVerticalBox->GetParent()->GetVisibility() == ESlateVisibility::Visible ?
			ESlateVisibility::Collapsed : ESlateVisibility::Visible;

		OnlineVerticalBox->GetParent()->SetVisibility(visibility);
	}	
}

void UFriendsListController::OnOfflineFriendsButtonClicked() const
{
	if(OfflineVerticalBox)
	{
		const ESlateVisibility visibility = OfflineVerticalBox->GetParent()->GetVisibility() == ESlateVisibility::Visible ?
			ESlateVisibility::Collapsed : ESlateVisibility::Visible;

		OfflineVerticalBox->GetParent()->SetVisibility(visibility);		
	}
}
