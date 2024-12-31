// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverFriendWidget.h"
#include "Components/TextBlock.h"

void UHoverFriendWidget::SetPlayerData(const FFriendsListData& friendData) const
{
	if(NickName)
	{
		NickName->SetText(friendData.NickName);
	}

	if(LastTimeOnline)
	{
		UE_LOG(LogTemp, Warning, TEXT("LastTimeOnline fiinciona"));

		
		FText LastOnlineText = FText::Format(
		FText::FromString(TEXT("Last time online: {0}")),
		friendData.LastTimeOnline
		);

		// Set the text on the NickName UI element
		LastTimeOnline->SetText(LastOnlineText);
	}

	if(PlayerPicture)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerPicture fiinciona"));

		FSlateBrush Brush;
		Brush.SetResourceObject(friendData.Image);

		PlayerPicture->SetBrush(Brush);
	}
}
