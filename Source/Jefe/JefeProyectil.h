
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JefeProyectil.generated.h"

UCLASS()
class JEFE_API AJefeProyectil : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Proyectil) 
		class USphereComponent* Colision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Proyectil, meta = (AllowPrivateAccess = "true")) 
		class UParticleSystemComponent* Particula;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Proyectil, meta = (AllowPrivateAccess = "true")) 
		class UStaticMeshComponent* Bala;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movimiento, meta = (AllowPrivateAccess = "true")) 
		class UProjectileMovementComponent* BalaMovimiento;
	
public:	
	AJefeProyectil();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()    
		void AlImpactar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION() 
		void AlDestruirse(AActor* MyOverlappedActor);

	FORCEINLINE class UProjectileMovementComponent* CogerBalaMovimiento() const { return BalaMovimiento; }
};
