// Michael Freaney, 2024
// michael.freaney324@gmail.com

#include "AttackSet.h"
#include "GameFramework/Character.h"

void FAttackSet::Init(AActor* InOwner)
{
	OwnerPtr = InOwner ? InOwner : nullptr;
	if (!OwnerPtr.IsValid())
	{
		UE_LOG(LogAoE, Warning, TEXT("No valid owner for attack set!"));
	}
}

void FAttackSet::Start()
{
	if (TelegraphTime > 0.f)
	{
		CreateTelegraphs();
	}
	else
	{
		SnapshotAttacks();
	}
}

void FAttackSet::CreateTelegraphs()
{
	//#TODO
}

void FAttackSet::SnapshotAttacks()
{
	//use owner to get all players
	UWorld* World = OwnerPtr->GetWorld();
	if (!World)
	{
		return;
	}

	TArray<ACharacter*> LiveCharacters;
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; It++)
	{
		APlayerController* PC = It->Get();
		if (!PC)
		{
			continue;
		}

		if (ACharacter* Player = Cast<ACharacter>(PC->GetPawn()))
		{
			LiveCharacters.Add(Player);
		}
	}

	for (FAoEAttack& Attack : AttackData)
	{
		TArray<ACharacter*> OutHitChars;
		Attack.SnapshotPlayers(LiveCharacters, OutHitChars);
	}
}

