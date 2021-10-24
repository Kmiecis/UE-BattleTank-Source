#include "TankPlayerController.h"

#include "Engine/World.h"
#include "TankAimingComponent.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

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

	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	FVector HitLocation;
	if (GetSightRayHitLocation(OUT HitLocation))
	{
		UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (ensure(AimingComponent != nullptr))
		{
			AimingComponent->AimAt(HitLocation);
		}
	}
	else
	{
		// TODO: Aim at location at certain distance
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	FVector LookDirection;
	bool HasLookDirection = GetLookDirection(OUT LookDirection);
	if (HasLookDirection)
	{
		return GetLookDirectionHitLocation(LookDirection, OUT HitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirectionHitLocation(const FVector& LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	bool HasHitResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	);
	if (HasHitResult)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0.0f);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector& LookDirection) const
{
	int32 SizeX, SizeY;
	GetViewportSize(OUT SizeX, OUT SizeY);

	FVector2D CrossHairLocation = FVector2D(SizeX * CrossHairXLocation, SizeY * CrossHairYLocation);

	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(CrossHairLocation.X, CrossHairLocation.Y, OUT WorldLocation, OUT LookDirection);
}
