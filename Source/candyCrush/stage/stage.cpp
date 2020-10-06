// Fill out your copyright notice in the Description page of Project Settings.


#include "stage.h"
#include "Components/BoxComponent.h"
#include "../blocks.h"

// Sets default values
Astage::Astage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	For_uniformScale = CreateDefaultSubobject<UBoxComponent>(TEXT("uniformScale"));
	RootComponent = For_uniformScale;

	plane1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wall1"));
	plane1->SetupAttachment(RootComponent);

	plane2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wall2"));
	plane2->SetupAttachment(RootComponent);

	plane3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottom"));
	plane3->SetupAttachment(RootComponent);

	TTS_1 = CreateDefaultSubobject<UBoxComponent>(TEXT("TTS1"));
	TTS_1->SetupAttachment(RootComponent);

	TTS_2 = CreateDefaultSubobject<UBoxComponent>(TEXT("TTS2"));
	TTS_2->SetupAttachment(RootComponent);

	TTS_3 = CreateDefaultSubobject<UBoxComponent>(TEXT("TTS3"));
	TTS_3->SetupAttachment(RootComponent);

	TTS_4 = CreateDefaultSubobject<UBoxComponent>(TEXT("TTS4"));
	TTS_4->SetupAttachment(RootComponent);

	TTS_5 = CreateDefaultSubobject<UBoxComponent>(TEXT("TTS5"));
	TTS_5->SetupAttachment(RootComponent);

	TTS_6 = CreateDefaultSubobject<UBoxComponent>(TEXT("TTS6"));
	TTS_6->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void Astage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Astage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	tracer(TTS_1->GetComponentLocation());
	tracer(TTS_2->GetComponentLocation());
	tracer(TTS_3->GetComponentLocation());
	tracer(TTS_4->GetComponentLocation());
	tracer(TTS_5->GetComponentLocation());
	tracer(TTS_6->GetComponentLocation());



}

void Astage::tracer(FVector start) {
	FHitResult OutHit;
	FVector End = FVector(start.X+500, start.Y, start.Z);
	FCollisionQueryParams CollisionParams;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, start, End, ECC_Visibility, CollisionParams))
	{

	}
	else {
		FActorSpawnParameters spawnPara;
		spawnPara.Owner = this;

		if (GetWorld()) {
			GetWorld()->SpawnActor<AActor>(theBlock, FVector(2370.0, start.Y, start.Z), FRotator(0), spawnPara);
		}
	}
}
