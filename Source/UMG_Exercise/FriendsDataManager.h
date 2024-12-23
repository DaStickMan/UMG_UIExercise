// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FriendsListData.h"
#include "FriendsDataManager.generated.h"

UENUM(BlueprintType)
enum class FriendsDataManagerOperationType : uint8
{
	Add UMETA(DisplayName = "Add"),
	Remove UMETA(DisplayName = "Remove"),
	Update UMETA(DisplayName = "Update")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDataChanged, FriendsDataManagerOperationType, OperationType, FFriendsListData, FriendData);

/**
 * 
 */
UCLASS()
class UMG_EXERCISE_API UFriendsDataManager : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Data")
	FOnDataChanged OnDataChanged;

	TArray<FFriendsListData*> LoadDataTable(const UDataTable* InDataTable);

	FFriendsListData* GetByNickName(const FText nickName);

	void UpdateStatus(const FText nickName);
	
private:
	UDataTable* DataTable;
	
};
