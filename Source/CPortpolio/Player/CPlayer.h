#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "CPlayer.generated.h"

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
	void OnWalk();
	void OffWalk();
	void OnMainAction();
	void OnSubAction();

	UFUNCTION()
		void OnTwoHand();

private: //Scene Component
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private: //Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

	/*UPROPERTY(VisibleDefaultsOnly)
		class UCFeetComponent* Feet;*/
};
