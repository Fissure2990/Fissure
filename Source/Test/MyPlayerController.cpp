#include "MyPlayerController.h"
#include "MyCharacter.h"

AMyPlayerController::AMyPlayerController()
{
    //인풋 매핑
    {
        // InputMappingContext 로드
        static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(TEXT("InputMappingContext'/Game/InputAction/InputAction.InputAction'")); // 수정: 경로 수정
        if (MappingContextFinder.Succeeded())
        {
            DefaultContext = MappingContextFinder.Object;
        }
    }
    //무브
    {

        static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionFinder(TEXT("InputAction'/Game/InputAction/Move.Move'")); // 수정: 경로 수정
        if (MoveActionFinder.Succeeded())
        {
            Move = MoveActionFinder.Object;
        }
    }
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

    EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (!Subsystem) return;
    Subsystem->AddMappingContext(DefaultContext, 0);
    SetupInputComponent();
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

    if (!EnhancedInputComponent) return;
    EnhancedInputComponent->BindAction(Move, ETriggerEvent::Triggered, this, &AMyPlayerController::OnMove);
}

void AMyPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
    AMyCharacter* Players = Cast<AMyCharacter>(GetPawn());
    if (!Players) return;

    if (Players)
    {
            Players->bUseControllerRotationYaw = false;
            const FRotator Rotation = K2_GetActorRotation();
            const FRotator YawRotation = FRotator(0.0, Rotation.Yaw, 0.0);
            const FVector ForwardVector = YawRotation.Vector();
            const FVector RightVector = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

            // 앞 뒤 이동
            const FVector ActionValue = InputActionValue.Get<FVector>();
            Players->AddMovementInput(ForwardVector, ActionValue.Y);
            // 좌 우 이동
            Players->AddMovementInput(RightVector, ActionValue.X);
        
    }

}
