#include "TankProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

ATankProjectile::ATankProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement"));
	MovementComponent->bAutoActivate = false;
}

void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATankProjectile::Launch(float Speed)
{
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MovementComponent->Activate();
}
