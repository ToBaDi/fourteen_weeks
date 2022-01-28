// © 2022 Mohammad Jamal Sarvarian No rights reserved


#include "TheTool.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

ATheTool::ATheTool()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = Collision;
	Collision->InitSphereRadius(100.f);
	Collision->SetSimulatePhysics(true);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(Collision, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
	FPMove = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FPMove"));
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
}

void ATheTool::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATheTool::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsOnGround())
	{
		FallVelocity = FallInitialVelocity;
	}
	else
	{
		FallVelocity *= FallMultiplier;
		FPMove->AddInputVector(FVector::DownVector * FallVelocity * DeltaTime);
	}
}

void ATheTool::SetupPlayerInputComponent(UInputComponent* const PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Turn", this, &ATheTool::Turn);
	PlayerInputComponent->BindAxis("Roll", this, &ATheTool::Roll);
	PlayerInputComponent->BindAxis("Look", this, &ATheTool::Look);
	PlayerInputComponent->BindAxis("Forward", this, &ATheTool::Forward);
	PlayerInputComponent->BindAxis("Right", this, &ATheTool::Right);
	PlayerInputComponent->BindAxis("Up", this, &ATheTool::Up);

	PlayerInputComponent->BindAction("ResetRoll", IE_Released, this, &ATheTool::ResetRoll);
	PlayerInputComponent->BindAction("TurnToRoll", IE_Pressed, this, &ATheTool::TurnToRollOn);
	PlayerInputComponent->BindAction("TurnToRoll", IE_Released, this, &ATheTool::TurnToRollOff);
}

void ATheTool::Turn(const float Amount)
{
	if (IsTurnToRoll)
	{
		Roll(Amount);
	}
	else
	{
		AddControllerYawInput(Amount * TurnSpeed);
	}
}

void ATheTool::Roll(const float Amount)
{
	AddControllerRollInput(Amount * RollSpeed);
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
	if (IsOnGround())
	{
		FPMove->AddInputVector(FVector::UpVector * (Amount * UpSpeed));
	}
}

void ATheTool::ResetRoll()
{
	FRotator NewRot{ GetControlRotation() };
	NewRot.Roll = 0;
	Controller->SetControlRotation(NewRot);
}

void ATheTool::TurnToRollOn()
{
	IsTurnToRoll = true;
}

void ATheTool::TurnToRollOff()
{
	IsTurnToRoll = false;
}

bool ATheTool::IsOnGround()
{
	FHitResult HitResult;
	const FVector StartTrace{ GetActorLocation() };
	const FVector EndTrace{ StartTrace + (FVector::DownVector * Height) };
	return GetWorld()->LineTraceSingleByChannel(
		HitResult, StartTrace,
		EndTrace, ECC_WorldStatic,
		FCollisionQueryParams());
}

