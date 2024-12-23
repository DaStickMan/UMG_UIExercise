#pragma once

#include "CoreMinimal.h"
#include "FriendsListData.generated.h"

USTRUCT(BlueprintType)
struct UMG_EXERCISE_API FFriendsListData: public FTableRowBase 
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText NickName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int64 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsConnected;
};
