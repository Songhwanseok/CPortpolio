#include "CPortpolioGameModeBase.h"
#include "Global.h"
#include "GameFramework/Hud.h"

ACPortpolioGameModeBase::ACPortpolioGameModeBase()
{
	CHelpers::GetClass(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
	CHelpers::GetClass(&HUDClass, "/Game/BP_CHUD");
}