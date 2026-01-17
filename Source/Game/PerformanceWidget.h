// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PerformanceWidget.generated.h"

/**
 * Виджет для отображения полной статистики производительности
 * Аналогично встроенному stat unit в Unreal Engine
 */
UCLASS()
class GAME_API UPerformanceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPerformanceWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Переключение видимости виджета
	UFUNCTION(BlueprintCallable, Category = "Performance")
	void ToggleVisibility();

	// Показать виджет
	UFUNCTION(BlueprintCallable, Category = "Performance")
	void ShowWidget();

	// Скрыть виджет
	UFUNCTION(BlueprintCallable, Category = "Performance")
	void HideWidget();

protected:
	// Текст для отображения всех метрик
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PerformanceText;

	// Интервал обновления (в секундах)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance Settings")
	float UpdateInterval;

	// Показывать ли виджет
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance Settings")
	bool bIsVisible;

private:
	float TimeSinceLastUpdate = 0.0f;
	
	// Кэшированные значения метрик
	float CurrentFPS = 0.0f;
	float FrameTime = 0.0f;
	float GameTime = 0.0f;
	float DrawTime = 0.0f;
	float RHITime = 0.0f;
	float GPUTime = 0.0f;
	float InputTime = 0.0f;
	float MemoryUsage = 0.0f;
	FString RenderResolution;
	int32 Draws = 0;
	int32 Primitives = 0;

	void UpdatePerformanceDisplay();
	void GatherPerformanceStats();
};
