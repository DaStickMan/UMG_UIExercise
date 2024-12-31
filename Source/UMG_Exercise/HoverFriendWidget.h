// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FriendsListData.h"
#include "Components/Image.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HoverFriendWidget.generated.h"

/**
 * 
 */
UCLASS()
class UMG_EXERCISE_API UHoverFriendWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY( meta = (BindWidget))
	class UTextBlock* NickName;

	UPROPERTY( meta = (BindWidget))
	class UTextBlock* LastTimeOnline;

	UPROPERTY( meta = (BindWidget))
	class UImage* PlayerPicture;
	
public:
	void SetPlayerData(const FFriendsListData& friendData) const;
};
