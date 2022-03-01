// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainAnimInstance.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_KWANG(TEXT("SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/KwangSunrise.KwangSunrise'"));
	if (SM_KWANG.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_KWANG.Object);
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.f), FRotator(0.f, -90.f, 0.f));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.f);

	static ConstructorHelpers::FObjectFinder<USoundCue> SC_ATTACK(TEXT("SoundCue'/Game/_MyContents/Character/Sound/Kwang_Effort_Attack.Kwang_Effort_Attack'"));
	if (SC_ATTACK.Succeeded())
	{
		AttackSound = SC_ATTACK.Object;
	}
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

void AMainCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UMainAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMainCharacter::OnAttackMontageEnded); // 바인드될 함수의 인자는 OnMontageEnded 정의 추적해서 들어가보면 있음
		AnimInstance->OnAttackHit.AddUObject(this, &AMainCharacter::AttackCheck); // 애님인스턴스에서 만든 델리게이트를 구독한것/ OnAttackHit에서 브로드캐스트하면 AttackCheck 함수 실행
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMainCharacter::Attack);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMainCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMainCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMainCharacter::Yaw);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMainCharacter::Pitch);

}

void AMainCharacter::UpDown(float Value)
{
	if (IsAttacking)
		return;
	// 정면기준으로 앞으로가야하고
	const FRotator ControllerRotator = Controller->GetControlRotation();
	const FRotator RotatorYaw = FRotator(0.f, ControllerRotator.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(RotatorYaw).GetUnitAxis(EAxis::X);

	AddMovementInput(Direction, Value);
}

void AMainCharacter::LeftRight(float Value)
{
	if (IsAttacking)
		return;
	// 정면기준으로 오른쪽으로 가야하니깐
	const FRotator ControllerRotator = Controller->GetControlRotation();
	const FRotator RotatorYaw = FRotator(0.f, ControllerRotator.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(RotatorYaw).GetUnitAxis(EAxis::Y);

	AddMovementInput(Direction, Value);
}

void AMainCharacter::Yaw(float Value)
{
	AddControllerYawInput(Value);
}

void AMainCharacter::Pitch(float Value)
{
	AddControllerPitchInput(Value);
}

void AMainCharacter::Attack()
{
	if (IsAttacking)
		return; 

	AnimInstance->PlayAttackMontage();
	AnimInstance->JumpToSection(AttackIndex);

	AttackIndex = (AttackIndex + 1) % 3;

	UGameplayStatics::PlaySound2D(this, AttackSound);

	IsAttacking = true;
}

void AMainCharacter::AttackCheck()
{
	// 애님 인스턴스에서 만든 애님 노티파이가 충돌 체크할 타이밍이라고 알려주는것임.
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 150.f;
	float AttackRadius = 50.f;

	// 충돌체크 함수
	bool bSweepResult = GetWorld()->SweepSingleByChannel(  
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, // config폴더의 DefaultEngine.ini 참고하면 있음 에디터에서 만든 Attack채널이 2번으로 설정 되어있음
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat(); // 잘 모르겠네
	FColor DrawColor = bSweepResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
}

void AMainCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}

