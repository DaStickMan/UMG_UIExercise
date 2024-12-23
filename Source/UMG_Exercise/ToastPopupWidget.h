// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToastPopupWidget.generated.h"

/**
 * 
 */
UCLASS()
class UMG_EXERCISE_API UToastPopupWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Toast")
	void ShowToast(const FText& Message, float Duration = 3.0f);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ToastMessageText;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* MoveInOutAnimation;

	float ToastDuration;
};
