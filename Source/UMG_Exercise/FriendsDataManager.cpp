// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendsDataManager.h"

TArray<FFriendsListData*> UFriendsDataManager::LoadDataTable(const UDataTable* InDataTable)
{;
	DataTable = const_cast<UDataTable*>(InDataTable);
	TArray<FFriendsListData*> FriendsData;
	InDataTable->GetAllRows<FFriendsListData>("", FriendsData);
	return FriendsData;
}

FFriendsListData* UFriendsDataManager::GetByNickName(const FText nickName)
{
	if (!DataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable is not valid."));
		return nullptr;
	}

	// Get all rows from the DataTable
	TArray<FFriendsListData*> FriendsData;
	DataTable->GetAllRows<FFriendsListData>("", FriendsData);

	for (FFriendsListData* FriendData : FriendsData)
	{
		if (FriendData && FriendData->NickName.ToString() == nickName.ToString()) 
		{
			return FriendData; 
		}
	}

	return nullptr;
}

void UFriendsDataManager::UpdateStatus(const FText nickName)
{
	FFriendsListData* friendData = GetByNickName(nickName);

	friendData->IsConnected = !friendData->IsConnected;
	OnDataChanged.Broadcast(FriendsDataManagerOperationType::Update, *friendData);
}
