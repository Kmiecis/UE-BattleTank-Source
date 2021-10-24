#include "TankAIController.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank != nullptr))
	{
		return;
	}

	EPathFollowingRequestResult::Type Result = MoveToActor(PlayerTank, AcceptanceRadius);

	APawn* ControlledTank = GetPawn();
	if (!ensure(ControlledTank != nullptr))
	{
		return;
	}

	UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent != nullptr))
	{
		return;
	}

	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->Fire();
}
