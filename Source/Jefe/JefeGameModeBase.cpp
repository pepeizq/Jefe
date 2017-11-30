#include "JefeGameModeBase.h"

#include "UObject/ConstructorHelpers.h"

#include "JefeHUD.h"

AJefeGameModeBase::AJefeGameModeBase() : Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/CaracterBP"));

	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = AJefeHUD::StaticClass();
}




