#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTPOLIO_API UCWeaponActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCWeaponActionComponent();

protected:
	virtual void BeginPlay() override;

};
