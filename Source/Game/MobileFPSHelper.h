// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSWidget.h"
#include "MobileFPSHelper.generated.h"

/**
 * Вспомогательный класс для управления FPS на мобильных устройствах
 * Поддерживает жесты для переключения FPS
 */
UCLASS()
class GAME_API AMobileFPSHelper : public AActor
{
	GENERATED_BODY()
	
public:	
	AMobileFPSHelper();

protected:
	virtual void BeginPlay() override;

	// Класс виджета FPS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS")
	TSubclassOf<UFPSWidget> FPSWidgetClass;

	// Экземпляр виджета FPS
	UPROPERTY()
	UFPSWidget* FPSWidgetInstance;

	// Включить FPS при старте
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS")
	bool bEnableFPSOnStart;

	// Жест для переключения FPS (тройное касание экрана)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS")
	bool bEnableTripleTapToggle;

	// Время между касаниями для тройного касания (в секундах)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS")
	float TripleTapTimeWindow;

private:
	float LastTapTime = 0.0f;
	int32 TapCount = 0;

	// Обработка касаний для переключения FPS
	void HandleTouchInput();
};
