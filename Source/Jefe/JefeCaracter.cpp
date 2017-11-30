#include "JefeCaracter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "JefeProyectil.h"

AJefeCaracter::AJefeCaracter()
{	
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	BaseGirarRate = 45.0f;    
	BaseMirarArribaRate = 45.0f;

	//-----------------------------

	Camara = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	
	Camara->SetupAttachment(GetCapsuleComponent());
	Camara->RelativeLocation = FVector(0, 0, 64.f);
	Camara->bUsePawnControlRotation = true;

	//-----------------------------

	Brazos = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));

	Brazos->SetOnlyOwnerSee(true); 
	Brazos->SetupAttachment(Camara);
	Brazos->bCastDynamicShadow = false; 
	Brazos->CastShadow = false;

	//-----------------------------

	Arma = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	
	Arma->SetOnlyOwnerSee(true);
	Arma->bCastDynamicShadow = false;
	Arma->CastShadow = false;
	//Arma->AttachToComponent(Brazos, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("GripPoint"));
	Arma->SetupAttachment(Brazos, TEXT("GripPoint"));

	//-----------------------------

	Bala = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn")); 
	Bala->SetupAttachment(Arma);

	//-----------------------------

}

void AJefeCaracter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJefeCaracter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJefeCaracter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(InputComponent);

	InputComponent->BindAction("Saltar", IE_Pressed, this, &ACharacter::Jump);    
	InputComponent->BindAction("Saltar", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("Disparar", IE_Pressed, this, &AJefeCaracter::AlDisparar);
	InputComponent->BindAction("Seguir", IE_Pressed, this, &AJefeCaracter::AlSeguir);

	InputComponent->BindAxis("MoverAdelanteAtras", this, &AJefeCaracter::MoverAdelanteAtras);    
	InputComponent->BindAxis("MoverDerechaIzquierda", this, &AJefeCaracter::MoverDerechaIzquierda);
	InputComponent->BindAxis("Girar", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("GirarRate", this, &AJefeCaracter::GirarAtRate);
	InputComponent->BindAxis("MirarArriba", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("MirarArribaRate", this, &AJefeCaracter::MirarArribaAtRate);	
}

void AJefeCaracter::MoverAdelanteAtras(float Valor)
{
	if (Valor != 0.0f) 
	{
		 AddMovementInput(GetActorForwardVector(), Valor);
	}
}

void AJefeCaracter::MoverDerechaIzquierda(float Valor) 
{
	if (Valor != 0.0f) 
	{        
		AddMovementInput(GetActorRightVector(), Valor);    
	} 
}

void AJefeCaracter::GirarAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseGirarRate * GetWorld()->GetDeltaSeconds());
}

void AJefeCaracter::MirarArribaAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseMirarArribaRate * GetWorld()->GetDeltaSeconds());
}

void AJefeCaracter::AlDisparar()
{
	//if (ProyectilClase != nullptr)
	//{
	//	if (GetWorld() != nullptr) 
	//	{ 
	//		GetWorld()->SpawnActor<AJefeProyectil>(ProyectilClase, Bala->GetComponentLocation(), Bala->GetComponentRotation());
	//	}
	//}

	AJefeProyectil* UnaBala = GetWorld()->SpawnActor<AJefeProyectil>(ProyectilClase, Bala->GetComponentLocation(), GetControlRotation());
	UnaBala->CogerBalaMovimiento()->HomingTargetComponent = TrackingSceneComponent;
}

void AJefeCaracter::AlSeguir()
{
	FVector MousePos;
	FVector MouseDir;
	FHitResult Hit;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);

	APlayerController* playerController = Cast<APlayerController>(GetController());

	if (GEngine->GameViewport != nullptr && playerController != nullptr)
	{
		FVector2D ScreenPos = GEngine->GameViewport->Viewport->GetSizeXY();

		playerController->DeprojectScreenPositionToWorld(ScreenPos.X / 2.0f, ScreenPos.Y / 2.0f, MousePos, MouseDir);
		MouseDir *= 100000.0f;

		GetWorld()->LineTraceSingleByObjectType(Hit, MousePos, MouseDir, ObjectQueryParams);

		if (Hit.bBlockingHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("TRACE HIT WITH %s"), *(Hit.GetActor()->GetName()));
			TrackingSceneComponent = Cast<USceneComponent>(Hit.GetActor()->GetComponentByClass(USceneComponent::StaticClass()));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Trace"));
			TrackingSceneComponent = nullptr;
		}
	} 
}