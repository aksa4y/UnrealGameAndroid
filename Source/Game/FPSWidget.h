// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "FPSWidget.generated.h"

/**
 * Виджет для отображения FPS на экране
 */
UCLASS()
class GAME_API UFPSWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFPSWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Переключение видимости виджета
	UFUNCTION(BlueprintCallable, Category = "FPS")
	void ToggleVisibility();

	// Показать виджет
	UFUNCTION(BlueprintCallable, Category = "FPS")
	void ShowFPS();

	// Скрыть виджет
	UFUNCTION(BlueprintCallable, Category = "FPS")
	void HideFPS();

protected:
	// Текст для отображения FPS
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FPSText;

	// Интервал обновления FPS (в секундах)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS Settings")
	float UpdateInterval;

	// Показывать ли миллисекунды
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS Settings")
	bool bShowMilliseconds;

	// Минимальный FPS для зеленого цвета
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS Settings")
	float GoodFPS;

	// Минимальный FPS для желтого цвета
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS Settings")
	float MediumFPS;

	// Показывать ли виджет (можно переключать во время игры)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS Settings")
	bool bIsVisible;

private:
	float TimeSinceLastUpdate = 0.0f;
	float CurrentFPS = 0.0f;
	float FrameTime = 0.0f;

	void UpdateFPSDisplay();
};
