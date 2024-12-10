// Fill out your copyright notice in the Description page of Project Settings.


#include "FriendRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UFriendRowWidget::SetFriendData(const FString& Name, const FString& Info, bool IsConnected) const
{
	if (NameTextBlock)
	{
		NameTextBlock->SetText(FText::FromString(Name));
	}

	if (LevelTextBlock)
	{
		LevelTextBlock->SetText(FText::FromString(Info));
	}

	if (StatusImage)
	{
		StatusImage->SetColorAndOpacity(IsConnected ? FColor::Green : FColor::Red);
	}
}
