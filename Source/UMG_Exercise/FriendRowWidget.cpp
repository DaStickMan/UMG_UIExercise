// Fill out your copyright notice in the Description page of Project Settings.


#include "FriendRowWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

void UFriendRowWidget::SetFriendData(const FFriendsListData& friendData)
{
	if (NameTextBlock)
	{
		NameTextBlock->SetText(friendData.NickName);
	}

	if (LevelTextBlock)
	{
		FText level = FText::AsNumber(friendData.Level);
		LevelTextBlock->SetText(level);
	}

	if (StatusImage)
	{
		StatusImage->SetColorAndOpacity(friendData.IsConnected ? FColor::Green : FColor::Red);
	}

	if (HoverFriendWidgetClass)
	{
		HoverWidgetInstance = CreateWidget<UHoverFriendWidget>(GetWorld(), HoverFriendWidgetClass);

		if(HoverWidgetInstance)
		{
			HoverWidgetInstance->SetPlayerData(friendData);
			UE_LOG(LogTemp, Warning, TEXT("Instancia fiinciona"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Instancia nao fiinciona"));
		}
	}
}

void UFriendRowWidget::NativeConstruct()
{
	if (HoverWidgetInstance)
	{
		SetToolTip(HoverWidgetInstance);
	}
	
	Super::NativeConstruct();
}
