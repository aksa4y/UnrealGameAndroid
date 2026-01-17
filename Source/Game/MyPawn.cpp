// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSWidgetClass = nullptr;
	FPSWidgetInstance = nullptr;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	// Автоматически включаем FPS через консольную команду (работает на всех платформах)
	if (GEngine)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			// Включаем отображение FPS через консольную команду
			GEngine->Exec(World, TEXT("stat fps"));
			UE_LOG(LogTemp, Log, TEXT("FPS display enabled via console command"));
		}
	}
	
	// Автоматически создаем виджет FPS (если задан класс)
	CreateFPSWidget();
}

void AMyPawn::CreateFPSWidget()
{
	if (FPSWidgetClass)
	{
		// Создаем виджет из класса
		FPSWidgetInstance = CreateWidget<UFPSWidget>(GetWorld(), FPSWidgetClass);
		if (FPSWidgetInstance)
		{
			FPSWidgetInstance->AddToViewport();
		}
	}
	else
	{
		// Если класс не задан, создаем напрямую (для мобильных устройств)
		// Это будет работать только если есть Blueprint виджет
		UE_LOG(LogTemp, Warning, TEXT("FPSWidgetClass не задан. Создайте Blueprint виджет на основе FPSWidget."));
	}
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

