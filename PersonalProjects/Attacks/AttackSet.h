// Michael Freaney, 2024
// michael.freaney324@gmail.com

#pragma once
#include "AoEAttack.h"
#include "AttackSet.generated.h"

USTRUCT()
struct FAttackSet
{
	GENERATED_BODY()
public:
	void Init(AActor* InOwner);

	UPROPERTY(EditAnywhere, Category = "Attack Settings")
	float TelegraphTime = 2.5f;

	UPROPERTY(EditAnywhere, Category = "Attack Settings")
	TArray<FAoEAttack> AttackData;

	void Start();
protected:
	void CreateTelegraphs();
	void SnapshotAttacks();

	UPROPERTY()
	TWeakObjectPtr<AActor> OwnerPtr;
};