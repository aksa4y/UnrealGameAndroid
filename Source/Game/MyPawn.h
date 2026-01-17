// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FPSWidget.h"
#include "MyPawn.generated.h"

UCLASS()
class GAME_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Виджет для отображения FPS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UFPSWidget> FPSWidgetClass;

	UPROPERTY()
	UFPSWidget* FPSWidgetInstance;

	// Создает и отображает виджет FPS
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateFPSWidget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
