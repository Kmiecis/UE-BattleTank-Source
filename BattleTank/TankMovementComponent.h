#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"

#include "TankMovementComponent.generated.h"

class UTankTrack;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack* NewLeftTrack, UTankTrack* NewRightTrack);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};