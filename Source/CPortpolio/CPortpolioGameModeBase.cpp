#include "CPortpolioGameModeBase.h"
#include "Global.h"

ACPortpolioGameModeBase::ACPortpolioGameModeBase()
{
	CHelpers::GetClass(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
	
}