#include "CEnemy.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CActionComponent.h"
#include "Components/CMontageComponent.h"

//Todo. ABP 만들기, ACEnemy 기능 만들기
ACEnemy::ACEnemy()
{
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &Montages, "Montages");

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "SkeletalMesh'/Game/Character/Mesh/Yaku_J_Ignite.Yaku_J_Ignite'");
	GetMesh()->SetSkeletalMesh(meshAsset);
}

void ACEnemy::BeginPlay()
{
	//Create Dynamic Material
	LowerMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), nullptr);
	UpperMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), nullptr);
	GetMesh()->SetMaterial(0, LowerMaterial);
	GetMesh()->SetMaterial(1, UpperMaterial);

	State->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);

	Super::BeginPlay();
	
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	Causer = DamageCauser;

	Action->AbortByDamaged();
	Status->DecreaseHealth(DamageValue);

	if (Status->IsDead())
	{
		State->SetDeadMode();
		return DamageValue;
	}

	State->SetHittedMode();

	return DamageValue;
}

void ACEnemy::ChangeBodyColor(FLinearColor InColor)
{
}

void ACEnemy::RestorColor()
{
}

void ACEnemy::Hitted()
{
	Montages->PlayHitted();

	FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FRotator rotation = FRotator(0, UKismetMathLibrary::FindLookAtRotation(start, target).Yaw, 0);
	SetActorRotation(rotation);

	FVector direction = (start - target).GetSafeNormal();
	LaunchCharacter(direction * LaunchValue * DamageValue, true, false);

	//ChangeBodyColor(FLinearColor::Red);

	//UKismetSystemLibrary::K2_SetTimer(this, "RestoreColor", 0.5f, false);
}

void ACEnemy::Dead()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->GlobalAnimRateScale = 0.f;

	FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FVector direction = (start - target).GetSafeNormal();
	FVector force = direction * LaunchValue * DamageValue;
	GetMesh()->AddForceAtLocation(force, start);

	Action->OffAllCollisions();

	UKismetSystemLibrary::K2_SetTimer(this, "End_Dead", 5.f, false);
}

void ACEnemy::End_Dead()
{
	Action->End_Dead();

	Destroy();
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Hitted:		Hitted();			break;
		case EStateType::Dead:		Dead();			break;
	}
}



