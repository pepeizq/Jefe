
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JefeHUD.generated.h"

UCLASS()
class JEFE_API AJefeHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AJefeHUD();

	virtual void DrawHUD() override;

private:   
	class UTexture2D* CrosshairTextura;

};
