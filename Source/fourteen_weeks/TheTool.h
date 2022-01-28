// © 2022 Mohammad Jamal Sarvarian No rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TheTool.generated.h"

UCLASS()
class FOURTEEN_WEEKS_API ATheTool final : public APawn
{
	GENERATED_BODY()

public:
	ATheTool();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(const float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* const PlayerInputComponent) override;

private:
	void Turn(const float Amount);
	void Look(const float Amount);
	void Forward(const float Amount);
	void Right(const float Amount);
	void Up(const float Amount);

	UPROPERTY(EditAnywhere)
	float TurnSpeed = 1.f;
	UPROPERTY(EditAnywhere)
	float LookSpeed = 1.f;
	UPROPERTY(EditAnywhere)
	float ForwardSpeed = 1.f;
	UPROPERTY(EditAnywhere)
	float RightSpeed = 1.f;
	UPROPERTY(EditAnywhere)
	float UpSpeed = 1.f;
	UPROPERTY(EditAnywhere)
	float Height = 200.f; 
	UPROPERTY(EditAnywhere)
	float FallInitialVelocity = 1.f;
	UPROPERTY(EditAnywhere)
	float FallMultiplier = 1.5f;
	
	
	float FallVelocity = 0.f;
	
	UPROPERTY(EditAnywhere)
	class USphereComponent* Collision;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* FPMove;
};
