// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayersListGameMode.h"


void APlayersListGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (FriendsListWidget)
	{
		FriendsListWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), FriendsListWidget);

		if (FriendsListWidgetInstance)
		{
			FriendsListWidgetInstance->AddToViewport();
		}
	}
}