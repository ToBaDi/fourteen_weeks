// Fill out your copyright notice in the Description page of Project Settings.


#include "TheTool.h"

// Sets default values
ATheTool::ATheTool()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATheTool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATheTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATheTool::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

