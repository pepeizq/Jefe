
#pragma once

#include "JefeProyectil.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JefeCaracter.generated.h"

UCLASS()
class JEFE_API AJefeCaracter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) 
		class USkeletalMeshComponent* Brazos;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) 
		class USkeletalMeshComponent* Arma;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) 
		class UCameraComponent* Camara;

public:
	AJefeCaracter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) 
		float BaseGirarRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) 
		float BaseMirarArribaRate;

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = Proyectil) 
		TSubclassOf<AJefeProyectil> ProyectilClase;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Proyectil)
		class USceneComponent* Bala;

protected:

	void MoverAdelanteAtras(float Val);

	void MoverDerechaIzquierda(float Val);

	void GirarAtRate(float Rate);

	void MirarArribaAtRate(float Rate);

	void AlDisparar();

	USceneComponent* TrackingSceneComponent;

	void AlSeguir();
	
};
