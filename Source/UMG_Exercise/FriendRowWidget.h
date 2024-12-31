// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HoverFriendWidget.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendRowWidget.generated.h"

/**
 * 
 */
UCLASS()
class UMG_EXERCISE_API UFriendRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LevelTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UImage* StatusImage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHoverFriendWidget> HoverFriendWidgetClass;
	
	void SetFriendData(const FFriendsListData& friendData);

protected:
	virtual void NativeConstruct() override;

private:
	UHoverFriendWidget* HoverWidgetInstance;
};
