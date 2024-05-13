// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyCharacter.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/BattleWizardPolyart/Meshes/WizardSM.WizardSM'"));
	if (Asset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(Asset.Object);
	}

     }
	{
		static ConstructorHelpers::FClassFinder<UAnimInstance> Asset(TEXT("/Script/Engine.AnimBlueprint'/Game/AB/NewAnimBlueprint1.NewAnimBlueprint1_C'"));
		if (Asset.Succeeded())
		{
			GetMesh()->SetAnimClass(Asset.Class);
		}
	}
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TEXT"));

	SpringArm->SetupAttachment(GetRootComponent());
	Text->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);
	

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 36.0f), FRotator(-20.0f, 0.0f, 0.0f));

	Camera->bUsePawnControlRotation = true;
	SpringArm->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	Text->SetRelativeLocation(FVector(0, 0, 120.0f));
	Text->SetHorizontalAlignment(EHTA_Center);
	Text->SetVerticalAlignment(EVRTA_TextCenter);
	
	GetCapsuleComponent()->SetCollisionProfileName("Player");
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnBeginOverlap);

	bReplicates = true;
	//bReplicateMovement = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//if (HasAuthority()) // 서버에서 실행
	//{
	//	Test = FMath::RandRange(0, 5);

	//}
	//FString NumberString = FString::FromInt(Test); // 정수를 FString으로 변환
	//FText NumberText = FText::FromString(NumberString);
	//Text->SetText(NumberText);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, Test);
}

void AMyCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "MCtests");
}