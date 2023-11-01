#include "CEnemy.h"
#include "Global.h"

//Todo. ABP 만들기, ACEnemy 기능 만들기
ACEnemy::ACEnemy()
{
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Status, "Status");

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "'/Game/Character/Mesh/SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(meshAsset);
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void ACEnemy::ChangebodyColor(FLinearColor InColor)
{
}

void ACEnemy::RestorColor()
{
}

void ACEnemy::Hitted()
{
}

void ACEnemy::Dead()
{
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
}

void ACEnemy::End_Dead()
{
}

