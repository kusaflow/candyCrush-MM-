// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "mainChar.generated.h"

UCLASS()
class CANDYCRUSH_API AmainChar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AmainChar();

	//checks if the you can select
	bool CanSelect;

	// stores all ref of the selecting blocks
	TArray<AActor*> Q_block;

	//tracks the last selected block
	FVector lastSelectedBlock;
	//current material selected
	int MatToSelect;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//selection start
	void SelStart();
	//selection ends
	void SelStop();
	//all selecting mechanic
	void selecting();
	//Go To Menu
	void GoToMenu();
	//Reset Game
	void ResetGame();


};
