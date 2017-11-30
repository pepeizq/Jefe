
#include "JefeBotRandomMovimiento.h"

#include "JefeBotIAController.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"

EBTNodeResult::Type 
UJefeBotRandomMovimiento::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ThisTree == nullptr || ThisController == nullptr)
	{
		ThisTree = OwnerComp.GetCurrentTree();
		ThisController = Cast<AJefeBotIAController>(OwnerComp.GetAIOwner());

		if (ThisTree == nullptr || ThisController == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Task assigned to incorrect AI type"));

			return EBTNodeResult::Failed;
		}
	}

	FNavLocation RandomPoint;

	if (GetWorld()->GetNavigationSystem()->GetRandomPointInNavigableRadius(ThisController->GetPawn()->GetActorLocation(), 5000.0f, RandomPoint))
	{
		ThisController->MoveTo(RandomPoint.Location);        
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}


