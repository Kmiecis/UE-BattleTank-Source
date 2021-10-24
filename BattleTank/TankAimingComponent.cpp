#include "TankAimingComponent.h"

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankProjectile.h"

#define OUT

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialize(UTankBarrel* NewBarrel, UTankTurret* NewTurret)
{
	Barrel = NewBarrel;
	Turret = NewTurret;
}

void UTankAimingComponent::AimAt(const FVector& AimLocation)
{
	if (!ensure(Barrel != nullptr))
	{
		return;
	}

	FVector LaunchVelocity;
	FVector LaunchLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool HasSuggestedVelocity = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT LaunchVelocity,
		LaunchLocation,
		AimLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (HasSuggestedVelocity)
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);

		FString Name = GetOwner()->GetName();
		float Time = GetWorld()->GetTimeSeconds();
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading)
	{
		if (!ensure(Barrel != nullptr))
		{
			return;
		}

		if (!ensure(ProjectileBlueprint != nullptr))
		{
			return;
		}

		FName SocketName = FName("Projectile");
		FVector SpawnLocation = Barrel->GetSocketLocation(SocketName);
		FRotator SpawnRotator = Barrel->GetSocketRotation(SocketName);
		ATankProjectile* TankProjectile = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotator);

		TankProjectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& Direction)
{
	if (ensure(Barrel != nullptr))
	{
		FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
		FRotator DirectionAsRotator = Direction.Rotation();
		FRotator DeltaRotator = DirectionAsRotator - BarrelRotator;

		Barrel->Elevate(DeltaRotator.Pitch);
	}
	if (ensure(Turret != nullptr))
	{
		FRotator BarrelRotator = Turret->GetForwardVector().Rotation();
		FRotator DirectionAsRotator = Direction.Rotation();
		FRotator DeltaRotator = DirectionAsRotator - BarrelRotator;

		Turret->Rotate(DeltaRotator.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel != nullptr))
	{
		return false;
	}

	FVector BarrelForward = Barrel->GetForwardVector();

	return !BarrelForward.Equals(AimDirection, 0.01f);
}
