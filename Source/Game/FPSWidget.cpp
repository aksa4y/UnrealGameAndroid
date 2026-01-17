// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSWidget.h"
#include "Engine/Engine.h"
#include "Components/TextBlock.h"

UFPSWidget::UFPSWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UpdateInterval = 0.1f;
	bShowMilliseconds = true;
	GoodFPS = 60.0f;
	MediumFPS = 30.0f;
	bIsVisible = true;
}

void UFPSWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Инициализация виджета
	if (FPSText)
	{
		FPSText->SetText(FText::FromString(TEXT("FPS: --")));
	}
}

void UFPSWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Обновляем FPS с заданным интервалом
	TimeSinceLastUpdate += InDeltaTime;
	FrameTime = InDeltaTime;

	if (TimeSinceLastUpdate >= UpdateInterval)
	{
		// Вычисляем FPS
		if (FrameTime > 0.0f)
		{
			CurrentFPS = 1.0f / FrameTime;
		}
		else
		{
			CurrentFPS = 0.0f;
		}

		UpdateFPSDisplay();
		TimeSinceLastUpdate = 0.0f;
	}
}

void UFPSWidget::UpdateFPSDisplay()
{
	if (!FPSText || !bIsVisible)
	{
		if (FPSText)
		{
			FPSText->SetVisibility(ESlateVisibility::Collapsed);
		}
		return;
	}

	// Показываем текст
	if (FPSText->GetVisibility() != ESlateVisibility::Visible)
	{
		FPSText->SetVisibility(ESlateVisibility::Visible);
	}

	// Формируем строку с FPS
	FString FPSString;
	
	if (bShowMilliseconds)
	{
		float Milliseconds = FrameTime * 1000.0f;
		FPSString = FString::Printf(TEXT("FPS: %.0f (%.1f ms)"), CurrentFPS, Milliseconds);
	}
	else
	{
		FPSString = FString::Printf(TEXT("FPS: %.0f"), CurrentFPS);
	}

	// Устанавливаем цвет в зависимости от FPS
	FSlateColor TextColor;
	if (CurrentFPS >= GoodFPS)
	{
		TextColor = FSlateColor(FLinearColor::Green); // Зеленый для хорошего FPS
	}
	else if (CurrentFPS >= MediumFPS)
	{
		TextColor = FSlateColor(FLinearColor::Yellow); // Желтый для среднего FPS
	}
	else
	{
		TextColor = FSlateColor(FLinearColor::Red); // Красный для низкого FPS
	}

	FPSText->SetText(FText::FromString(FPSString));
	FPSText->SetColorAndOpacity(TextColor);
}

void UFPSWidget::ToggleVisibility()
{
	bIsVisible = !bIsVisible;
	if (FPSText)
	{
		FPSText->SetVisibility(bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UFPSWidget::ShowFPS()
{
	bIsVisible = true;
	if (FPSText)
	{
		FPSText->SetVisibility(ESlateVisibility::Visible);
	}
}

void UFPSWidget::HideFPS()
{
	bIsVisible = false;
	if (FPSText)
	{
		FPSText->SetVisibility(ESlateVisibility::Collapsed);
	}
}
