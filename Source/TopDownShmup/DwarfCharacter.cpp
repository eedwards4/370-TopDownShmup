// Fill out your copyright notice in the Description page of Project Settings.


#include "DwarfCharacter.h"
#include "AIDwarfController.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

ADwarfCharacter::ADwarfCharacter()
{
	AIControllerClass = AAIDwarfController::StaticClass();
	ConstructorHelpers::FObjectFinder<UAnimMontage> AttkAnim(TEXT("AnimMontage'/Game/Characters/DwarfGrunt/Anims/Attack_1_new_Montage.Attack_1_new_Montage'"));
	AttackAnim = AttkAnim.Object;
	ConstructorHelpers::FObjectFinder<UAnimMontage> DieAnim(TEXT("AnimMontage'/Game/Characters/DwarfGrunt/Anims/Death2_Montage.Death2_Montage'"));
	DeathAnim = DieAnim.Object;
}

// Attack
void ADwarfCharacter::StartAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorld()->GetTimerManager().SetTimer(HitTimer, this, &ADwarfCharacter::Hit, AttackAnim->GetPlayLength(), true);
}

void ADwarfCharacter::StopAttack()
{
	StopAnimMontage(AttackAnim);
	GetWorld()->GetTimerManager().ClearTimer(HitTimer);
}

void ADwarfCharacter::Hit()
{
	UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->TakeDamage(HammerDamage, FDamageEvent(), GetInstigatorController(), this);
}

// Take damage
float ADwarfCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Dwarf hit!"), true);
		//Reduce health points
		MyHealth -= ActualDamage;
		if (MyHealth <= 0.0f)
		{
			// We're dead
			SetCanBeDamaged(false); // Don't allow further damage
			// UnPossess the AI controller
			GetController()->UnPossess();
			// Remove the dwarf from the world
			GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ADwarfCharacter::Die, DeathAnim->GetPlayLength() - 0.25f, false);
			// Stop attack animation
			StopAttack();
			PlayAnimMontage(DeathAnim);
		}
	}
	return ActualDamage;
}

void ADwarfCharacter::Die()
{
	GetWorld()->GetTimerManager().ClearTimer(DeathTimer);
	this->Destroy();
}


