#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CStateComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class CPORTPOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "OwnerCharacter")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "OwnerCharacter")
		float Direction;
};
