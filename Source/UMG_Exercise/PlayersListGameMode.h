// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FriendsListWidget.h"
#include "GameFramework/GameModeBase.h"
#include "PlayersListGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UMG_EXERCISE_API APlayersListGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> FriendsListWidget;

	UUserWidget* FriendsListWidgetInstance;
};
