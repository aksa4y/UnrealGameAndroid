// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSWidget.h"
#include "FPSPlayerController.generated.h"

/**
 * Player Controller с автоматическим отображением FPS
 */
UCLASS()
class GAME_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFPSPlayerController();

protected:
	virtual void BeginPlay() override;

	// Класс виджета FPS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UFPSWidget> FPSWidgetClass;

	// Экземпляр виджета FPS
	UPROPERTY()
	UFPSWidget* FPSWidgetInstance;

	// Создает и отображает виджет FPS
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateFPSWidget();
};
