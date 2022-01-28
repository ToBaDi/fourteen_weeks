// © 2022 Mohammad Jamal Sarvarian No rights reserved


#include "TheTool.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

ATheTool::ATheTool()
{
	PrimaryActorTick.bCanEverTick = false;
	
	PlayerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = PlayerCollision;
	PlayerCollision->InitSphereRadius(100.f);
	PlayerCollision->SetSimulatePhysics(true);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(PlayerCollision, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
	FPMove = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FPMove"));
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
}

void ATheTool::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATheTool::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATheTool::SetupPlayerInputComponent(UInputComponent* const PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &ATheTool::Turn);
	PlayerInputComponent->BindAxis("Look", this, &ATheTool::Look);
	PlayerInputComponent->BindAxis("Forward", this, &ATheTool::Forward);
	PlayerInputComponent->BindAxis("Right", this, &ATheTool::Right);
	PlayerInputComponent->BindAxis("Up", this, &ATheTool::Up);
}

void ATheTool::Turn(const float Amount)
{
	AddControllerYawInput(Amount * TurnSpeed);
}

void ATheTool::Look(const float Amount)
{
	AddControllerPitchInput(Amount * LookSpeed);
}

void ATheTool::Forward(const float Amount)
{
	const FVector Dir{ FVector::ForwardVector.RotateAngleAxis(GetActorRotation().Yaw, FVector::UpVector) };
	FPMove->AddInputVector(Dir * (Amount * ForwardSpeed));
}

void ATheTool::Right(const float Amount)
{
	const FVector Dir{ FVector::RightVector.RotateAngleAxis(GetActorRotation().Yaw, FVector::UpVector) };
	FPMove->AddInputVector(Dir * (Amount * RightSpeed));
}

void ATheTool::Up(const float Amount)
{
	FPMove->AddInputVector(FVector::UpVector * (Amount * UpSpeed));
}

