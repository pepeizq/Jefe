
#pragma once

#include "BehaviorTree/BehaviorTree.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JefeBotCaracter.generated.h"

UCLASS()
class JEFE_API AJefeBotCaracter : public ACharacter
{
	GENERATED_BODY()

public:
	AJefeBotCaracter();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = IA)
		const float CogerVida();

	UPROPERTY(EditAnywhere, Category = Pawn)
		class UBehaviorTree* Comportamiento;

private:
	UPROPERTY()    
		float Vida;
	
};
