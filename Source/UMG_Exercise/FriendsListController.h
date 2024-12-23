// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"

#include "FriendRowWidget.h"
#include "FriendsListData.h"
#include "FriendsDataManager.h"

#include "Blueprint/UserWidget.h"
#include "FriendsListController.generated.h"

/**
 * 
 */
UCLASS()
class UMG_EXERCISE_API UFriendsListController : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(RowType="FriendsListData"))
	FDataTableRowHandle Friends;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friends")
	TSubclassOf<UFriendRowWidget> FriendRowWidgetClass;  // Pointer to the FriendRowWidget blueprint


	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY( meta = (BindWidget))
	UVerticalBox* OnlineVerticalBox;

	UPROPERTY( meta = (BindWidget))
	UVerticalBox* OfflineVerticalBox;

	UPROPERTY( meta = (BindWidget))
	UButton* OnlineFriendsButton;

	UPROPERTY( meta = (BindWidget))
	UButton* OfflineFriendsButton;

	UFriendsDataManager* DataManager;
	
	void AddFriend(const FFriendsListData& Friend);
	void UpdateStatus(const FFriendsListData&  Text);

private:
	
	UFUNCTION()
	void HandleDataChanged(FriendsDataManagerOperationType type, FFriendsListData nickName);

	UFUNCTION()
	void OnOnlineFriendsButtonClicked();
	
	UFUNCTION()
	void OnOfflineFriendsButtonClicked();

	UFUNCTION(BlueprintCallable)
	void StartRandomStatusUpdates();

	UFUNCTION(BlueprintCallable)
	void RandomlyChangePlayerStatus();

	FTimerHandle RandomStatusTimerHandle;

	TMap<FString, UFriendRowWidget*> FriendsWidgetMap;

	FString GetFriendNickNameByPosition(int32 Index);	
};
