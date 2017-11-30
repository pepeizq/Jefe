
#include "JefeBotIAController.h"

#include "BehaviorTree/BlackboardComponent.h" 
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "JefeBotCaracter.h"
#include "JefeCaracter.h"
#include "Math/UnrealMathUtility.h"

AJefeBotIAController::AJefeBotIAController()
{ 
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));    
	check(BlackboardComp);    
	
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));    
	check(BehaviorTreeComp); 
}

void AJefeBotIAController::Possess(APawn* InPawn) 
{
	Super::Possess(InPawn);

	//AJefeBotCaracter* possessedPawn = Cast<AJefeBotCaracter>(InPawn);
	//
	//if (InPawn != nullptr) 
	//{
	//	BlackboardComp->InitializeBlackboard(*(possessedPawn->Comportamiento->BlackboardAsset));
	//	BehaviorTreeComp->StartTree(*(possessedPawn->Comportamiento));
	//}

	ControlledChar = Cast<AJefeBotCaracter>(InPawn);

	if (InPawn != nullptr) 
	{
		BlackboardComp->InitializeBlackboard(*(ControlledChar->Comportamiento->BlackboardAsset));
		BehaviorTreeComp->StartTree(*(ControlledChar->Comportamiento));
		BossStateBlackboardKey = BlackboardComp->GetKeyID("BossState");
	}

	TargetBlackboardKey = BlackboardComp->GetKeyID("TargetToFollow");
}

UBlackboardComponent* AJefeBotIAController::GetBlackboard() 
{ 
	return BlackboardComp; 
}

void AJefeBotIAController::Tick(float DeltaTime) 
{
	EBossState bossState;

	if (ControlledChar->CogerVida() > 66.0f) 
	{ 
		bossState = EBossState::BS_FOLLOW; 
	}
	else if (ControlledChar->CogerVida() > 33.0f) 
	{ 
		bossState = EBossState::BS_TURRET; 
	}
	else 
	{ 
		bossState = EBossState::BS_FINAL; 
	}

	BlackboardComp->SetValue<UBlackboardKeyType_Enum>(BossStateBlackboardKey, (uint8)bossState);

	if (bIsTracking && Target != nullptr)
	{
		FVector CharLoc = ControlledChar->GetActorLocation();
		FVector dirToTarget = Target->GetActorLocation() - CharLoc;
		FRotator rotToTarget = dirToTarget.Rotation();

		ControlledChar->SetActorRotation(FMath::Lerp(ControlledChar->GetActorRotation(), rotToTarget, DeltaTime * 5));
	}
}

void AJefeBotIAController::SeguirAlObjetivo()
{
	Target = Cast<AJefeCaracter>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(TargetBlackboardKey));

	if (Target != nullptr) 
	{ 
		bIsTracking = true; 
	}
}

void AJefeBotIAController::PararSeguimiento()
{ 
	bIsTracking = false;    
	Target = nullptr; 
}

void AJefeBotIAController::DispararBalas()
{
	if (Target)
	{
		for (int i = 1; i <= 5; ++i)
		{
			float fAngle = 16 + i * 26;            
			FVector circlePoint;  

			circlePoint.Y = (FMath::Cos(PI / 2) * FMath::Sin((fAngle * PI / 180.0f)));
			circlePoint.Z = (FMath::Sin(PI / 2) * FMath::Sin((fAngle * PI / 180.0f)));
			circlePoint.X = (FMath::Cos((fAngle * PI / 180.0f)));

			FRotator charRot = ControlledChar->GetActorRotation(); 
			charRot.Yaw = charRot.Yaw + 90.0f; 
			circlePoint = charRot.RotateVector(circlePoint);

			FVector SpawnLoc = ControlledChar->GetActorLocation() + circlePoint * 180.0f;
			AJefeProyectil* pThisProj = GetWorld()->SpawnActor<AJefeProyectil>(Target->ProyectilClase, SpawnLoc, ControlledChar->GetActorRotation());

			pThisProj->CogerBalaMovimiento()->HomingTargetComponent = Cast<USceneComponent>(Target->GetComponentByClass(USceneComponent::StaticClass()));
		}
	}
}