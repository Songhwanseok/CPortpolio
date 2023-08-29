#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "CPlayer.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttackSignature, )

UCLASS()
class CPORTPOLIO_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Axis Event
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);
	
	//Action Event
	//void OnAttack();

private:
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;
};
