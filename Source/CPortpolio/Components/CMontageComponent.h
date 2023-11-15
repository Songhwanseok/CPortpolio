#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CStateComponent.h"
#include "CMontageComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EStateType Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTPOLIO_API UCMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMontageComponent();

protected:
	virtual void BeginPlay() override;

public:
	void PlayHitted();
	void PlayDead();
		
private:
	void PlayAnimMontage(EStateType InStateType);

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;

private:
	FMontageData* Datas[(int32)EStateType::MAX];

};
