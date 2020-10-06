// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "kusaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CANDYCRUSH_API UkusaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	int T_Of_Block = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	int MovesLeft = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	int Score = 0;


	
};
