#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData_structs.h"
#include "CActionData.generated.h"

UCLASS()
class CPORTPOLIO_API UCActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	void BeginPlay(class ACharacter* InOwnerCharacter, UCActionData_structs** OutSpawned);

private:
	FString GetCustomActorLabel(class ACharacter* InOwnerCharacter, FString InMiddleName);

public:
	/*UPROPERTY(EditAnywhere, Category = "Attachment")
		TSubclassOf<class ACAttachment> AttachmentClass;*/

	/*UPROPERTY(EditAnywhere, Category = "Equipment")
		TSubclassOf<class ACEquipment> EquipmentClass;*/

	//UPROPERTY(EditAnywhere, Category = "Equipment")
	//	FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere, Category = "Equipment")
		FLinearColor EquipmentColor;

	UPROPERTY(EditAnywhere, Category = "DoAction")
		TSubclassOf<class ACDoAction> DoActionClass;

	UPROPERTY(EditAnywhere, Category = "DoAction")
		TArray<FDoActionData> DoActionDatas;
};
