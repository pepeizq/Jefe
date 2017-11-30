
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "JefeBotAgro.generated.h"

UCLASS()
class JEFE_API UJefeBotAgro : public UBTService
{
	GENERATED_BODY()
	
protected:    
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:    
	UBehaviorTree* ThisTree;    
	class AJefeBotIAController* ThisController;    
	class AJefeBotCaracter* ThisAICharacter;
		
};
