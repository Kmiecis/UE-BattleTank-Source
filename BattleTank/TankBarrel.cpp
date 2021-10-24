#include "TankBarrel.h"

#include "Engine/World.h"

void UTankBarrel::Elevate(float Speed)
{
	Speed = FMath::Clamp(Speed, -1.0f, 1.0f);

	float ElevationChange = Speed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	float Elevation = GetRelativeRotation().Pitch + ElevationChange;
	Elevation = FMath::Clamp(Elevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0.0f, 0.0f));
}
