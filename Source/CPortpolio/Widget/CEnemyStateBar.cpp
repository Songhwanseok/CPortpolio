#include "CEnemyStateBar.h"
#include "Components/ProgressBar.h"

void UCEnemyStateBar::NativeConstruct()
{

}

void UCEnemyStateBar::UpdateHealth_Implementation(float InCurrentHealth, float InMaxHealth)
{
	HealthBar->SetPercent(InCurrentHealth / InMaxHealth);
}
