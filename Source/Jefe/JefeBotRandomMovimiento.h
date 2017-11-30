
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "JefeBotRandomMovimiento.generated.h"

UCLASS()
class JEFE_API UJefeBotRandomMovimiento : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:
	UBehaviorTree* ThisTree;
	class AJefeBotIAController* ThisController;
	
};
