#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class CPORTPOLIO_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void ChangeBodyColor(FLinearColor InColor);

	UFUNCTION()
		void RestorColor();

private:
	void Hitted();
	void Dead();

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
		void End_Dead();

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontageComponent* Montages;

private:
	UPROPERTY(EditAnywhere)
		float LaunchValue = 25.f;

private:
	class UMaterialInstanceDynamic* UpperMaterial;
	class UMaterialInstanceDynamic* LowerMaterial;

	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue;

};
