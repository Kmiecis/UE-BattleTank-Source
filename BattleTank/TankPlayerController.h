#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirectionHitLocation(const FVector& LookDirection, FVector& HitLocation) const;
	bool GetLookDirection(FVector& LookDirection) const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);

private:
	UPROPERTY(EditDefaultsOnly) float CrossHairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly) float CrossHairYLocation = 0.33333f;
	UPROPERTY(EditDefaultsOnly) float LineTraceRange = 1000000.0f; // 10 km
};
