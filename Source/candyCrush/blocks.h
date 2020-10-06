// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "blocks.generated.h"

UCLASS()
class CANDYCRUSH_API Ablocks : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Ablocks();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* sm_block;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		class UMaterial* mat1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		class UMaterial* mat2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		class UMaterial* mat3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		class UMaterial* mat4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		class UMaterial* mat5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		class UMaterial* isSelectedMat;
	

	int blockType = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void isSelected(bool isSel);

	void SetMat();
};
