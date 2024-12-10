// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendsDataManager.h"

TArray<FFriendsListData*> UFriendsDataManager::LoadDataTable(const UDataTable* InDataTable)
{;
	DataTable = InDataTable;
	TArray<FFriendsListData*> FriendsData;
	DataTable->GetAllRows<FFriendsListData>("", FriendsData);
	return FriendsData;
}

void UFriendsDataManager::UpdateData(const FFriendsListData& UpdatedRow) const
{
	OnDataChanged.Broadcast();
}
