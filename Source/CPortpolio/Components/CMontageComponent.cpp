#include "CMontageComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

UCMontageComponent::UCMontageComponent()
{

}


void UCMontageComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr)
	{
		CLog::Log("DataTable is not set");
		return;
	}

	TArray<FMontageData*> datas;
	DataTable->GetAllRows<FMontageData>("", datas);

	for (int32 i = 0; i < (int32)EStateType::MAX; i++)
	{
		for (const auto& data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;

				break;
			}
		}
	}
}

void UCMontageComponent::PlayHitted()
{
	PlayAnimMontage(EStateType::Hitted);
}

void UCMontageComponent::PlayDead()
{
	PlayAnimMontage(EStateType::Dead);
}

void UCMontageComponent::PlayAnimMontage(EStateType InStateType)
{
	ACharacter* ownerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(ownerCharacter);

	const FMontageData* data = Datas[(int32)InStateType];

	if (!!data && !!data->AnimMontage)
		ownerCharacter->PlayAnimMontage(data->AnimMontage, data->PlayRate, data->StartSection);
}

