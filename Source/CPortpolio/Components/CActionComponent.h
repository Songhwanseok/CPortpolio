#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, TwoHand, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChangedSignature, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTPOLIO_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
		class UCActionData_Spawned* GetCurrentData() { return Datas[(int32)Type]; }

	UFUNCTION(BlueprintPure)
		class UCActionData* GetCurrentDataAsset() { return DataAssets[(int32)Type]; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EActionType::Unarmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTwoHandMode() { return Type == EActionType::TwoHand; }

public:
	UFUNCTION(BlueprintCallable) void SetUnarmedMode();
	UFUNCTION(BlueprintCallable) void SetTwoHandMode();

public:
	void DoAction();
	void OffAllCollisions();
	void AbortByDamaged();
	void End_Dead();

private:
	void SetMode(EActionType InNewType);
	void ChangeType(EActionType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChangedSignature OnActionTypeChanged; 

private:
	UPROPERTY(EditDefaultsOnly)
		class UCActionData* DataAssets[(int32)EActionType::Max];

private:
	EActionType Type;

	UPROPERTY()
		class UCActionData_Spawned* Datas[(int32)EActionType::Max];
};
