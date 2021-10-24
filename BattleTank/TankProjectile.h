#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TankProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLETANK_API ATankProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATankProjectile();
	virtual void Tick(float DeltaTime) override;
	void Launch(float Speed);
	
protected:
	virtual void BeginPlay() override;

private:
	UProjectileMovementComponent* MovementComponent = nullptr;
};
