#include "CBTService_Melee.h"
#include "Global.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
//#include "Enemy/CAIController.h"
#include "Enemy/CEnemy_AI.h"
#include "Player/CPlayer.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "Melee";
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Todo. AIcontroller 생성
	//ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	//CheckNull(controller);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	ACEnemy_AI* enemy = Cast<ACEnemy_AI>(controller->GetPawn());
	CheckNull(enemy);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(enemy);
	CheckNull(stateComp);

	//Hitted
	if (stateComp->IsHittedMode())
	{
		behaviorComp->SetHittedMode();
		return;
	}

	//Get Player from BB
	ACPlayer* player = behaviorComp->GetPlayerKey();

	//No Perceived Player
	if (player == nullptr)
	{
		//Todo. 적이 아군 base로 오도록 이동코드 작성
		/*if (patrolComp->IsPathValid())
		{
			behaviorComp->SetPatrolMode();
			return;
		}*/

		behaviorComp->SetWaitMode();
		return;
	}

	//Perceived Player
	UCStateComponent* playerStateComp = CHelpers::GetComponent<UCStateComponent>(player);
	if (!!playerStateComp)
	{
		if (playerStateComp->IsDeadMode())
		{
			behaviorComp->SetWaitMode();
			return;
		}
	}

	//-> Get Distance to Player
	float distance = enemy->GetDistanceTo(player);

	//-> Is in Attack Range
	if (distance < controller->GetBehaviorRange())
	{
		behaviorComp->SetActionMode();
		return;
	}

	//-> Is in Sight Range
	if (distance < controller->GetSightRadius())
	{
		behaviorComp->SetApproachMode();
		return;
	}


}
