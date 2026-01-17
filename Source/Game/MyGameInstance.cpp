// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "PerformanceWidget.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "HAL/IConsoleManager.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PerformanceWidgetClass = nullptr;
	PerformanceWidgetInstance = nullptr;
	bAutoCreateWidget = true;
}

void UMyGameInstance::Init()
{
	Super::Init();

	// Включаем консольное отображение FPS и полной статистики
	// Используем таймер для задержки, так как мир может быть еще не готов в Init()
	if (bAutoEnableConsoleFPS)
	{
		// Пытаемся включить сразу, если мир доступен
		UWorld* World = GetWorld();
		if (World)
		{
			// Пробуем включить через таймер с небольшой задержкой для надежности
			FTimerHandle TimerHandle;
			World->GetTimerManager().SetTimer(TimerHandle, this, &UMyGameInstance::EnableConsoleFPS, 1.0f, false);
		}
		else
		{
			// Если мир недоступен в Init(), попробуем включить позже при создании виджета
			UE_LOG(LogTemp, Warning, TEXT("World not available in Init(), will enable console FPS when widget is created"));
		}
	}
}

void UMyGameInstance::EnableConsoleFPS()
{
	// Включаем консольное отображение FPS и полной статистики
	if (GEngine)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			// Включаем отображение FPS (показывает FPS в левом верхнем углу)
			GEngine->Exec(World, TEXT("stat fps"));
			
			// Включаем полную статистику (Frame, Game, Draw, GPU, Input, Mem, RenderRes, Draws, Prims)
			GEngine->Exec(World, TEXT("stat unit"));
			
			// Дополнительно включаем отображение FPS через другой способ для надежности
			// Используем консольную переменную напрямую
			IConsoleVariable* ShowFPS = IConsoleManager::Get().FindConsoleVariable(TEXT("stat.fps"));
			if (ShowFPS)
			{
				ShowFPS->Set(1);
			}
			
			IConsoleVariable* ShowUnit = IConsoleManager::Get().FindConsoleVariable(TEXT("stat.unit"));
			if (ShowUnit)
			{
				ShowUnit->Set(1);
			}
			
			UE_LOG(LogTemp, Log, TEXT("Console FPS and stats display enabled in GameInstance"));
		}
		else
		{
			// Попытка через глобальный Exec, если мир недоступен
			// Это работает не всегда, но лучше попытаться
			GEngine->Exec(nullptr, TEXT("stat fps"));
			GEngine->Exec(nullptr, TEXT("stat unit"));
			UE_LOG(LogTemp, Warning, TEXT("Attempted to enable console FPS without world context"));
		}
	}
}

void UMyGameInstance::Shutdown()
{
	// Удаляем виджет при завершении
	if (PerformanceWidgetInstance)
	{
		PerformanceWidgetInstance->RemoveFromParent();
		PerformanceWidgetInstance = nullptr;
	}

	Super::Shutdown();
}

void UMyGameInstance::CreatePerformanceWidget()
{
	// Включаем консольное отображение FPS при создании виджета (когда мир точно доступен)
	if (bAutoEnableConsoleFPS)
	{
		EnableConsoleFPS();
	}

	if (PerformanceWidgetClass)
	{
		// Создаем виджет из класса
		UWorld* World = GetWorld();
		if (World)
		{
			PerformanceWidgetInstance = CreateWidget<UPerformanceWidget>(World, PerformanceWidgetClass);
			if (PerformanceWidgetInstance)
			{
				PerformanceWidgetInstance->AddToViewport();
				UE_LOG(LogTemp, Log, TEXT("Performance widget created and added to viewport"));
			}
		}
	}
	else
	{
		// Если класс не задан, выводим предупреждение
		UE_LOG(LogTemp, Warning, TEXT("PerformanceWidgetClass не задан в GameInstance. Создайте Blueprint виджет на основе PerformanceWidget."));
	}
}

void UMyGameInstance::TogglePerformanceWidget()
{
	if (PerformanceWidgetInstance)
	{
		PerformanceWidgetInstance->ToggleVisibility();
	}
	else
	{
		// Если виджет не создан, создаем его
		CreatePerformanceWidget();
	}
}
