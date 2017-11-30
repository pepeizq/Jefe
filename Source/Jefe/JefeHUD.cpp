#include "JefeHUD.h"

#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "Public/CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

AJefeHUD::AJefeHUD()
{     
	static ConstructorHelpers::FObjectFinder<UTexture2D> Textura(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	
	CrosshairTextura = Textura.Object;
}

void AJefeHUD::DrawHUD()
{
	Super::DrawHUD();

	const FVector2D Centro(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	const FVector2D CrosshairPosicion((Centro.X - (CrosshairTextura->GetSurfaceWidth() * 0.5)), (Centro.Y - (CrosshairTextura->GetSurfaceHeight() * 0.5f)));

	FCanvasTileItem TileItem(CrosshairPosicion, CrosshairTextura->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;

	Canvas->DrawItem(TileItem);
}



