// © 2022 Mohammad Jamal Sarvarian No rights reserved


#include "TheTool.h"

#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

ATheTool::ATheTool()
{
	PrimaryActorTick.bCanEverTick = true;
	 
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);
	Mesh->SetLinearDamping(8.f);
	Mesh->SetAngularDamping(6.f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->FieldOfView = 100.f;
	Camera->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
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

	bOnGround = IsOnGround();

	if (bOnGround)
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
	if (bTurnToRoll)
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
	if (bOnGround)
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
	bTurnToRoll = true;
}

void ATheTool::TurnToRollOff()
{
	bTurnToRoll = false;
}

bool ATheTool::IsOnGround() const
{
	FHitResult HitResult;
	const FVector StartTrace{ GetActorLocation() };
	const FVector EndTrace{ StartTrace + (FVector::DownVector * Height) };
	const bool Result{
		GetWorld()->LineTraceSingleByChannel(
			HitResult, StartTrace,
			EndTrace, ECC_Visibility,
			FCollisionQueryParams())
	};
	GetWorld()->LineTraceSingleByProfile()
	
	// DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red,false, 1.f);
	
	return Result;
}

