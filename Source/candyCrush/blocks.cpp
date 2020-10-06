// Fill out your copyright notice in the Description page of Project Settings.


#include "blocks.h"

// Sets default values
Ablocks::Ablocks()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sm_block = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wall1"));
	RootComponent = sm_block;

}

// Called when the game starts or when spawned
void Ablocks::BeginPlay()
{
	Super::BeginPlay();
	
	blockType = (int)FMath::FRandRange(1,6);
	SetMat();
}

// Called every frame
void Ablocks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Ablocks::isSelected(bool isSel) {
	if (isSel) {
		sm_block->SetMaterial(0, isSelectedMat);
	}
	else {
		SetMat();
	}
}

void Ablocks::SetMat() {
	if (blockType == 1) {
		sm_block->SetMaterial(0, mat1);
	}
	else if (blockType == 2) {
		sm_block->SetMaterial(0, mat2);
	}
	else if (blockType == 3) {
		sm_block->SetMaterial(0, mat3);
	}
	else if (blockType == 4) {
		sm_block->SetMaterial(0, mat4);
	}
	else if (blockType == 5) {
		sm_block->SetMaterial(0, mat5);
	}
}
