
#include "JefeBotAgro.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "DrawDebugHelpers.h" 
#include "Jefe.h"
#include "JefeBotCaracter.h"
#include "JefeBotIAController.h"

void UJefeBotAgro::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (ThisTree == nullptr || ThisController == nullptr || ThisAICharacter == nullptr)
	{
		ThisTree = OwnerComp.GetCurrentTree();
		ThisController = Cast<AJefeBotIAController>(OwnerComp.GetAIOwner());
		ThisAICharacter = Cast<AJefeBotCaracter>(ThisController->GetPawn());

		if (ThisTree == nullptr || ThisController == nullptr || ThisAICharacter == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Warning Agro Service performed on invalid AI"));
			return;
		}
	}

	//-------------------------------

	FCollisionQueryParams SphereSweepParams(FName(TEXT("AgroCheckSweep")), true, ThisAICharacter);
	FCollisionObjectQueryParams ObjectQuery(ECC_GameTraceChannel1);
	FHitResult HitOut(ForceInit);

	DrawDebugSphere(ThisAICharacter->GetWorld(), ThisAICharacter->GetActorLocation(), 1500, 12, FColor::Red, false, 4.0f);

	bool bResult = ThisAICharacter->GetWorld()->SweepSingleByObjectType(HitOut, ThisAICharacter->GetActorLocation(), ThisAICharacter->GetActorLocation() + FVector(0.0f, 0.0f, 10.0f), FQuat(), ObjectQuery, FCollisionShape::MakeSphere(1500), SphereSweepParams);
	
	//-------------------------------

	if (bResult) 
	{
		ThisController->GetBlackboard()->SetValueAsObject(TEXT("TargetToFollow"), HitOut.GetActor());
		ThisController->GetBlackboard()->SetValueAsVector(TEXT("HomeLocation"), ThisAICharacter->GetActorLocation());
		ThisController->GetBlackboard()->SetValueAsVector(TEXT("TargetLocation"), HitOut.GetActor()->GetActorLocation());
		ThisController->SeguirAlObjetivo();
	}
	else 
	{ 
		ThisController->GetBlackboard()->SetValueAsObject(TEXT("TargetToFollow"), nullptr); 
		ThisController->PararSeguimiento();
	}
}


