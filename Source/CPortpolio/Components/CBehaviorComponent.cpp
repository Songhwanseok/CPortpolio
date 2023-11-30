#include "CBehaviorComponent.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/CPlayer.h"

UCBehaviorComponent::UCBehaviorComponent()
{
}


void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

}

bool UCBehaviorComponent::IsWaitMode()
{
	return GetTypeFromBB() == EBehaviorType::Wait;
}

bool UCBehaviorComponent::IsApproachMode()
{
	return GetTypeFromBB() == EBehaviorType::Approach;
}

bool UCBehaviorComponent::IsActionMode()
{
	return GetTypeFromBB() == EBehaviorType::Action;
}

bool UCBehaviorComponent::IsMoveToBaseMode()
{
	return GetTypeFromBB() == EBehaviorType::MoveToBase;
}

bool UCBehaviorComponent::IsHittedMode()
{
	return GetTypeFromBB() == EBehaviorType::Hitted;
}

EBehaviorType UCBehaviorComponent::GetTypeFromBB()
{
	return (EBehaviorType)Blackboard->GetValueAsEnum(BehaviorKey);
}

void UCBehaviorComponent::SetWaitMode()
{
	ChangeType(EBehaviorType::Wait);
}

void UCBehaviorComponent::SetApproachMode()
{
	ChangeType(EBehaviorType::Approach);
}

void UCBehaviorComponent::SetActionMode()
{
	ChangeType(EBehaviorType::Action);
}

void UCBehaviorComponent::SetMoveToBaseMode()
{
	ChangeType(EBehaviorType::MoveToBase);
}

void UCBehaviorComponent::SetHittedMode()
{
	ChangeType(EBehaviorType::Hitted);
}

ACPlayer* UCBehaviorComponent::GetPlayerKey()
{
	return Cast<ACPlayer>(Blackboard->GetValueAsObject(PlayerKey));
}

FVector UCBehaviorComponent::GetLocationKey()
{
	return Blackboard->GetValueAsVector(LocationKey);
}

void UCBehaviorComponent::ChangeType(EBehaviorType InNewType)
{
	EBehaviorType prev = GetTypeFromBB();
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InNewType);

	if (OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(prev, InNewType);
}
