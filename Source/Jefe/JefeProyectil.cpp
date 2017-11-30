
#include "JefeProyectil.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "JefeBotCaracter.h"
#include "Particles/ParticleSystemComponent.h"

AJefeProyectil::AJefeProyectil()
{
	PrimaryActorTick.bCanEverTick = true;

	Colision = CreateDefaultSubobject <USphereComponent>(TEXT("SphereComp"));
	Colision->InitSphereRadius(10.0f);
	Colision->BodyInstance.SetCollisionProfileName("BlockAll");
	Colision->OnComponentHit.AddDynamic(this, &AJefeProyectil::AlImpactar);
	OnDestroyed.AddDynamic(this, &AJefeProyectil::AlDestruirse);

	//----------------------------

	Colision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Colision->CanCharacterStepUpOn = ECB_No;
	RootComponent = Colision;

	//----------------------------

	Bala = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("MeshComp"));
	Bala->SetupAttachment(Colision);
	Bala->SetCollisionProfileName(TEXT("NoCollision"));

	//----------------------------

	Particula = CreateDefaultSubobject <UParticleSystemComponent>(TEXT("ParticleComp"));
	Particula->bAutoActivate = false;    
	Particula->SetupAttachment(Bala);

	//----------------------------

	BalaMovimiento = CreateDefaultSubobject <UProjectileMovementComponent>(TEXT("ProjectileComp"));
	BalaMovimiento->UpdatedComponent = Colision;    
	BalaMovimiento->InitialSpeed = 3000.f;
	BalaMovimiento->MaxSpeed = 3000.f;    
	BalaMovimiento->bRotationFollowsVelocity = true;
	BalaMovimiento->bIsHomingProjectile = true; 
	BalaMovimiento->HomingAccelerationMagnitude = 10000.0f;

	//----------------------------

	InitialLifeSpan = 3.0f;
}

void AJefeProyectil::BeginPlay()
{
	Super::BeginPlay();

}

void AJefeProyectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJefeProyectil::AlImpactar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->GetClass()->IsChildOf(this->StaticClass())) 
	{
		Colision->SetCollisionProfileName(TEXT("NoCollision"));        
		Colision->bGenerateOverlapEvents = false;        
		
		Bala->SetVisibility(false);
		
		Particula->Activate();        
		Particula->DetachFromParent(true);
	}

	if (OtherActor->GetClass()->IsChildOf(AJefeBotCaracter::StaticClass()))
	{
		FDamageEvent DamageEvent(UDamageType::StaticClass());
		OtherActor->TakeDamage(10.0f, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
	}
}

void AJefeProyectil::AlDestruirse(AActor* MyOverlappedActor)
{    
}
