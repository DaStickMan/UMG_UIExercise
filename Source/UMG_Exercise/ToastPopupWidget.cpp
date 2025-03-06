// Fill out your copyright notice in the Description page of Project Settings.


#include "ToastPopupWidget.h"

#include "Components/TextBlock.h"

void UToastPopupWidget::ShowToast(const FText& Message, float Duration)
{
	ToastMessageText->SetText(Message);
	PlayAnimation(MoveInOutAnimation);
}

void UToastPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
