#include "CStateComponent.h"

UCStateComponent::UCStateComponent()
{
}


void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCStateComponent::SetIdleMode()
{
	SetState(EStateType::Idle);
}

void UCStateComponent::SetEquipMode()
{
	SetState(EStateType::Equip);
}

void UCStateComponent::SetAttackMode()
{
	SetState(EStateType::Attack);
}

void UCStateComponent::SetState(EStateType InState)
{
	State = InState;
}

