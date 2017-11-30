
#include "JefeBotCaracter.h"

#include "GameFramework/PawnMovementComponent.h"

AJefeBotCaracter::AJefeBotCaracter()
{
	PrimaryActorTick.bCanEverTick = true;

	Vida = 100.0f;

	GetMovementComponent()->NavAgentProps.AgentHeight = 320.0f;    
	GetMovementComponent()->NavAgentProps.AgentRadius = 160.0f;
}

float AJefeBotCaracter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Vida -= Damage;
	return Damage;
}

const float AJefeBotCaracter::CogerVida()
{ 
	return Vida; 
}

