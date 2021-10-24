#include "TankTurret.h"

#include "Engine/World.h"

void UTankTurret::Rotate(float Speed)
{
	Speed = FMath::Clamp(Speed, -1.0f, 1.0f);

	float RotationChange = Speed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Rotation = GetRelativeRotation().Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.0f, Rotation, 0.0f));
}
