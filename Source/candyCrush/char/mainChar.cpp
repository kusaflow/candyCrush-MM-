// Fill out your copyright notice in the Description page of Project Settings.


#include "mainChar.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../blocks.h"
#include "DrawDebugHelpers.h"
#include "../gameInst/kusaGameInstance.h"

// Sets default values
AmainChar::AmainChar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AmainChar::BeginPlay()
{
	Super::BeginPlay();
	CanSelect = false;

	UkusaGameInstance* gameInst = Cast<UkusaGameInstance>(GetGameInstance());
	gameInst->Score = 0;
	gameInst->MovesLeft =15;
}

// Called every frame
void AmainChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	UkusaGameInstance* gameInst = Cast<UkusaGameInstance>(GetGameInstance());
	
	if (gameInst->MovesLeft <= 0) {
		UGameplayStatics::OpenLevel(GetWorld(), "Map_gameUp");
	}
	
	if (CanSelect)
		selecting();


}

// Called to bind functionality to input
void AmainChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("SelectionStart", IE_Pressed, this, &AmainChar::SelStart);
	PlayerInputComponent->BindAction("SelectionStart", IE_Released, this, &AmainChar::SelStop);

	PlayerInputComponent->BindAction("exitGame", IE_Pressed, this, &AmainChar::GoToMenu);
	PlayerInputComponent->BindAction("Reset", IE_Pressed, this, &AmainChar::ResetGame);
}

void AmainChar::SelStart() {
	// reset 
	CanSelect = true;
	lastSelectedBlock.X = 0;
	lastSelectedBlock.Y = 0;
	lastSelectedBlock.Z = 0;
}

void AmainChar::SelStop() {
	//clear the blocks 
	CanSelect = false;

	UkusaGameInstance* gameInst = Cast<UkusaGameInstance>(GetGameInstance());

	if (Q_block.Num() >= 3) {
		gameInst->MovesLeft--;
		while (Q_block.Num() != 0) {
			Ablocks* toDest = Cast<Ablocks>(Q_block.Pop());
			if (toDest) {
				gameInst->Score += 10;
				//toDest->isCurrently_Selected = false;
				//toDest->isSelected();
				toDest->Destroy();
			}
		}
	}
	else {
		while (Q_block.Num() != 0) {
			Ablocks* toDest = Cast<Ablocks>(Q_block.Pop());
			if (toDest) {
				toDest->isCurrently_Selected = false;
				toDest->isSelected();
				//toDest->Destroy();
			}
		}
	}

}

void AmainChar::GoToMenu() {
	//Go Back To Menu
	UGameplayStatics::OpenLevel(GetWorld(), "Map_startingScreen");
}

void AmainChar::ResetGame() {
	UGameplayStatics::OpenLevel(GetWorld(), "GameMap");
}


void AmainChar ::selecting() {
	
	APlayerController* contr = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector mouseLoc, mouseDir;

	//mouse projection to world
	contr->DeprojectMousePositionToWorld(mouseLoc, mouseDir);

	mouseDir *= 10000;

	FHitResult OutHit;
	FVector start = mouseLoc;
	FVector End = FVector(mouseLoc.X + mouseDir.X, mouseLoc.Y + mouseDir.Y, mouseLoc.Z + mouseDir.Z);
	FCollisionQueryParams CollisionParams;

	//DrawDebugLine(GetWorld(), start , End, FColor::Green, false, 1, 0, 1);

	//UE_LOG(LogTemp, Warning, TEXT("%f,%f,%f"), start.X, start.Y, start.Z);
	//UE_LOG(LogTemp, Warning, TEXT("%f,%f,%f"), End.X, End.Y, End.Z);
	//UE_LOG(LogTemp, Warning, TEXT("%f,%f,%f"), lastSelectedBlock.X, lastSelectedBlock.Y, lastSelectedBlock.Z);
	
	if (GetWorld()->LineTraceSingleByChannel(OutHit, start, End, ECC_Visibility, CollisionParams))
	{
		// Get The ref
		Ablocks* block = Cast<Ablocks>(OutHit.Actor);

		if (block) {
			FVector bl_Loc = block->GetActorLocation();
			//Select Accordingly
			if (!block->isCurrently_Selected) {
				if (lastSelectedBlock.IsZero()) {
					block->isCurrently_Selected = true;
					block->isSelected();
					Q_block.Push(block);
					lastSelectedBlock = bl_Loc;
					MatToSelect = block->blockType;
				}
				/*
				else if (bl_Loc.Y == lastSelectedBlock.Y  
					&& bl_Loc.Z > lastSelectedBlock.Z - 250
					&& bl_Loc.Z < lastSelectedBlock.Z + 250) {
					// for vert
					if (block->blockType == MatToSelect) {
						block->isCurrently_Selected = true;
						block->isSelected();
						Q_block.Push(block);
						lastSelectedBlock = bl_Loc;
					}
				}
				else if ((bl_Loc.Z > lastSelectedBlock.Z - 10 || bl_Loc.Z < lastSelectedBlock.Z + 10)
					&& bl_Loc.Y > lastSelectedBlock.Y - 250
					&& bl_Loc.Y < lastSelectedBlock.Y + 250) {
					//for horz
					if (block->blockType == MatToSelect) {
						block->isCurrently_Selected = true;
						block->isSelected();
						Q_block.Push(block);
						lastSelectedBlock = bl_Loc;
					}
				}*/
				else if (bl_Loc.Y > lastSelectedBlock.Y-210
					&& bl_Loc.Y < lastSelectedBlock.Y + 210
					&& bl_Loc.Z > lastSelectedBlock.Z - 210
					&& bl_Loc.Z < lastSelectedBlock.Z + 210) {
					///////////
					
					if (bl_Loc.Z < -400) {
						if (block->blockType == MatToSelect) {
							block->isCurrently_Selected = true;
							block->isSelected();
							Q_block.Push(block);
							lastSelectedBlock = bl_Loc;
						}
					}else if (bl_Loc.Y == lastSelectedBlock.Y) {
						if (block->blockType == MatToSelect) {
							block->isCurrently_Selected = true;
							block->isSelected();
							Q_block.Push(block);
							lastSelectedBlock = bl_Loc;
						}
					}
					else if ((bl_Loc.Z > lastSelectedBlock.Z - 50 && bl_Loc.Z < lastSelectedBlock.Z + 50)) {
						if (block->blockType == MatToSelect) {
							block->isCurrently_Selected = true;
							block->isSelected();
							Q_block.Push(block);
							lastSelectedBlock = bl_Loc;
						}
					}
					else {
						if (lastSelectedBlock.Z < -400) {
							if (block->blockType == MatToSelect) {
								block->isCurrently_Selected = true;
								block->isSelected();
								Q_block.Push(block);
								lastSelectedBlock = bl_Loc;
							}
						}
					}

				}

				
			}
			else {
				lastSelectedBlock = bl_Loc;
			}
		}

	}
}


