
#pragma once

#include "BehaviorTree/BlackboardComponent.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "JefeBotIAController.generated.h"

UENUM(BlueprintType) 
enum class EBossState : uint8 
{ 
	BS_FOLLOW = 0 UMETA(DisplayName = "Follow"), 
	BS_TURRET = 1 UMETA(DisplayName = "Turret"), 
	BS_FINAL = 2 UMETA(DisplayName = "Final") 
};

UCLASS()
class JEFE_API AJefeBotIAController : public AAIController
{
	GENERATED_BODY()
	
public:    
	AJefeBotIAController();    
	
	virtual void Possess(APawn* InPawn) override;        
	
	UBlackboardComponent* GetBlackboard();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Comportamiento) 
		void SeguirAlObjetivo();

	UFUNCTION(BlueprintCallable, Category = Comportamiento)
		void PararSeguimiento();

	UFUNCTION(BlueprintCallable, Category = Comportamiento) 
		void DispararBalas();

protected:    
	UPROPERTY(BlueprintReadWrite, Category = Comportamiento)
		class UBlackboardComponent* BlackboardComp;

	UPROPERTY(BlueprintReadWrite, Category = Comportamiento)
		class UBehaviorTreeComponent* BehaviorTreeComp;
	
private:
	class AJefeBotCaracter* ControlledChar; 
	
	FBlackboard::FKey BossStateBlackboardKey;

	FBlackboard::FKey TargetBlackboardKey; 
	
	class AJefeCaracter* Target; 
	
	bool bIsTracking;
};
