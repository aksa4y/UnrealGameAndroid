// Fill out your copyright notice in the Description page of Project Settings.

#include "MobileFPSHelper.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

AMobileFPSHelper::AMobileFPSHelper()
{
	PrimaryActorTick.bCanEverTick = true;
	bEnableFPSOnStart = true;
	bEnableTripleTapToggle = true;
	TripleTapTimeWindow = 0.5f;
	FPSWidgetClass = nullptr;
	FPSWidgetInstance = nullptr;
	LastTapTime = 0.0f;
	TapCount = 0;
}

void AMobileFPSHelper::BeginPlay()
{
	Super::BeginPlay();

	// Создаем виджет FPS
	if (FPSWidgetClass && bEnableFPSOnStart)
	{
		FPSWidgetInstance = CreateWidget<UFPSWidget>(GetWorld(), FPSWidgetClass);
		if (FPSWidgetInstance)
		{
			FPSWidgetInstance->AddToViewport();
			if (!bEnableFPSOnStart)
			{
				FPSWidgetInstance->HideFPS();
			}
		}
	}

	// Включаем статистику FPS через консольную команду (работает на Android)
	if (bEnableFPSOnStart)
	{
		if (GEngine)
		{
			GEngine->Exec(GetWorld(), TEXT("stat fps"));
		}
	}
}

void AMobileFPSHelper::HandleTouchInput()
{
	// Эта функция может быть вызвана из Blueprint для обработки жестов
	// В Blueprint можно добавить обработку тройного касания
}
