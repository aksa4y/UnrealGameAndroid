// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * Кастомный GameInstance для управления виджетом производительности
 */
UCLASS()
class GAME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;
	virtual void Shutdown() override;

	// Класс виджета производительности (можно задать в Blueprint)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
	TSubclassOf<class UPerformanceWidget> PerformanceWidgetClass;

	// Экземпляр виджета производительности
	UPROPERTY(BlueprintReadOnly, Category = "Performance")
	class UPerformanceWidget* PerformanceWidgetInstance;

	// Создать виджет производительности
	UFUNCTION(BlueprintCallable, Category = "Performance")
	void CreatePerformanceWidget();

	// Переключить видимость виджета
	UFUNCTION(BlueprintCallable, Category = "Performance")
	void TogglePerformanceWidget();

	// Включить консольное отображение FPS автоматически
	UFUNCTION(BlueprintCallable, Category = "Performance")
	void EnableConsoleFPS();

private:
	// Автоматически создавать виджет при старте
	UPROPERTY(EditDefaultsOnly, Category = "Performance")
	bool bAutoCreateWidget = true;

	// Автоматически включать консольное отображение FPS
	UPROPERTY(EditDefaultsOnly, Category = "Performance")
	bool bAutoEnableConsoleFPS = true;
};
