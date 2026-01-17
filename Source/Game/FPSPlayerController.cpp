// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

AFPSPlayerController::AFPSPlayerController()
{
	FPSWidgetClass = nullptr;
	FPSWidgetInstance = nullptr;
}

void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Автоматически включаем FPS через консольную команду (работает на всех платформах, включая Android)
	if (GEngine)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			// Включаем отображение FPS через консольную команду
			GEngine->Exec(World, TEXT("stat fps"));
			UE_LOG(LogTemp, Log, TEXT("FPS display enabled via console command in PlayerController"));
		}
	}

	// Автоматически создаем виджет FPS
	CreateFPSWidget();
}

void AFPSPlayerController::CreateFPSWidget()
{
	if (FPSWidgetClass)
	{
		// Создаем виджет из класса
		FPSWidgetInstance = CreateWidget<UFPSWidget>(this, FPSWidgetClass);
		if (FPSWidgetInstance)
		{
			FPSWidgetInstance->AddToViewport();
		}
	}
	else
	{
		// Если класс не задан, выводим предупреждение
		UE_LOG(LogTemp, Warning, TEXT("FPSWidgetClass не задан в FPSPlayerController. Создайте Blueprint виджет на основе FPSWidget."));
	}
}
