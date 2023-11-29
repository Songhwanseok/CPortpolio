#include "CHealthWidget.h"
#include "Global.h"
#include "Components/ProgressBar.h"

//void UCHealthWidget::UpdateHealth_Implementation(float InCurrentHealth, float InMaxHealth)
//{
//	HealthBar->SetPercent(InCurrentHealth / InMaxHealth);
//	CLog::Log("Update Health Called");
//}

void UCHealthWidget::UpdateHealth(float InCurrentHealth, float InMaxHealth)
{
	HealthBar->SetPercent(InCurrentHealth / InMaxHealth);
	CLog::Log("Update Health Called");
}
