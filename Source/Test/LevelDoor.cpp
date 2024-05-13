// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDoor.h"
#include "GameFramework/PlayerController.h"
#include "MyCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelDoor::ALevelDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));

	RootComponent = Mesh;

	Capsule->SetupAttachment(GetRootComponent());

	Capsule->SetCapsuleHalfHeight(300.0f);
	Capsule->SetCapsuleRadius(300.0f);
	Capsule->SetCollisionProfileName("OverlapAllDynamic");
	
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ALevelDoor::OnBeginOverlap);
}

void ALevelDoor::BeginPlay()
{
	Super::BeginPlay();
	TestTest();
}

void ALevelDoor::TestTest()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Test");
}

void ALevelDoor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Other) return; 
	
		if (GetWorld())
		{
			GetWorld()->ServerTravel(TEXT("/Game/Maps/Test2"));
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "Level");
		}
		
	

		//AMyCharacter* Char = Cast<AMyCharacter>(Other);
		//if (Char)
		//{
		//	APlayerController* Pic = Cast<APlayerController>(Char->GetController());
		//	if (Pic)
		//	{
		//		Char->Test = FMath::RandRange(0, 5);
		//		FString NumberString = FString::FromInt(Test); // 정수를 FString으로 변환
		//		FText NumberText = FText::FromString(NumberString);
		//		Char->Text->SetText(NumberText);
		//		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "TEXT");
		//	}
		//}
			
		
	
}
