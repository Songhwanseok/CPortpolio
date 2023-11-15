#include "CPlayer.h"
#include "../Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Camera/CameraComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CActionComponent.h"
#include "Components/CMontageComponent.h"

ACPlayer::ACPlayer()
{
	CHelpers::CreateSceneComponent(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateSceneComponent(this, &Camera, "Camera", SpringArm);

	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &Montages, "Montages");
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &State, "State");
	//CHelpers::CreateActorComponent(this, &Feet, "Feet");

	USkeletalMesh* meshAsset;
	CHelpers::GetAsset<USkeletalMesh>(&meshAsset, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(meshAsset);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 200.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);

	//Action
	PlayerInputComponent->BindAction("MainAction", EInputEvent::IE_Pressed, this, &ACPlayer::OnMainAction);
	PlayerInputComponent->BindAction("SubAction", EInputEvent::IE_Pressed, this, &ACPlayer::OnSubAction);
	PlayerInputComponent->BindAction("TwoHand", EInputEvent::IE_Pressed, this, &ACPlayer::OnTwoHand);
}

void ACPlayer::OnMoveForward(float InAxis)
{
	CheckTrue(FMath::IsNearlyZero(InAxis));
	CheckFalse(Status->IsCanMove());

	FRotator controlRotationYaw = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(controlRotationYaw).GetForwardVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnMoveRight(float InAxis)
{
	CheckTrue(FMath::IsNearlyZero(InAxis));
	CheckFalse(Status->IsCanMove());

	FRotator controlRotationYaw = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(controlRotationYaw).GetRightVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	AddControllerYawInput(100 * InAxis * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnVerticalLook(float InAxis)
{ 
	AddControllerPitchInput(100 * InAxis * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnWalk()
{
}

void ACPlayer::OffWalk()
{
}

void ACPlayer::OnMainAction()
{
	Action->DoAction();
}

void ACPlayer::OnSubAction()
{
	CLog::Print("SubAction");
}

void ACPlayer::OnTwoHand()
{
	CheckFalse(State->IsIdleMode());

	Action->SetTwoHandMode();
}

