// Fill out your copyright notice in the Description page of Project Settings.


#include "mainChar.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../blocks.h"
#include "DrawDebugHelpers.h"

// Sets default values
AmainChar::AmainChar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	For_uniformScale = CreateDefaultSubobject<UBoxComponent>(TEXT("cameraManupulatorBox"));
	RootComponent = For_uniformScale;

	plane1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wall1"));
	plane1->SetupAttachment(RootComponent);

	plane2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wall2"));
	plane2->SetupAttachment(RootComponent);

	plane3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottom"));
	plane3->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AmainChar::BeginPlay()
{
	Super::BeginPlay();
	CanSelect = false;
}

// Called every frame
void AmainChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	selecting();
}

// Called to bind functionality to input
void AmainChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("SelectionStart", IE_Pressed, this, &AmainChar::SelStart);
	PlayerInputComponent->BindAction("SelectionStart", IE_Released, this, &AmainChar::SelStop);

}

void AmainChar::SelStart() {
	CanSelect = true;
}

void AmainChar::SelStop() {
	CanSelect = false;
}


void AmainChar ::selecting() {
	
	APlayerController* contr = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector mouseLoc, mouseDir;

	contr->DeprojectMousePositionToWorld(mouseLoc, mouseDir);

	mouseDir *= 10000;

	FHitResult OutHit;
	FVector start = mouseLoc;
	FVector End = FVector(mouseLoc.X + mouseDir.X, mouseLoc.Y + mouseDir.Y, mouseLoc.Z + mouseDir.Z);
	FCollisionQueryParams CollisionParams;

	//DrawDebugLine(GetWorld(), start , End, FColor::Green, false, 1, 0, 1);

	UE_LOG(LogTemp, Warning, TEXT("%f,%f,%f"), start.X, start.Y, start.Z);
	UE_LOG(LogTemp, Warning, TEXT("%f,%f,%f"), End.X, End.Y, End.Z);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, start, End, ECC_Visibility, CollisionParams))
	{
		UE_LOG(LogTemp, Warning, TEXT("555555555555555555555555555555555"));
		Ablocks* block = Cast<Ablocks>(OutHit.Actor);

		if (block) {
			block->Destroy();
		}

	}
}


