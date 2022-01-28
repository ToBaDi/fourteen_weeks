// © 2022 Mohammad Jamal Sarvarian No rights reserved


#include "TheTool.h"

#include "Camera/CameraComponent.h"

ATheTool::ATheTool()
{
	PrimaryActorTick.bCanEverTick = false;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	

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

}

