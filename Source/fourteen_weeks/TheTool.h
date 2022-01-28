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
	UPROPERTY()
	class UCameraComponent* Camera;  
};
