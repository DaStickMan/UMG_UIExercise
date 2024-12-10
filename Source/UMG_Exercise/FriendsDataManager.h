// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FriendsListData.h"
#include "FriendsDataManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDataChanged);

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
	void UpdateData(const FFriendsListData& UpdatedRow) const;
    
private:
	const UDataTable* DataTable;
	
};
