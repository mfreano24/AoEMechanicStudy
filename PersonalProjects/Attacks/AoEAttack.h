// Michael Freaney, 2024
// michael.freaney324@gmail.com

#pragma once

#include "AoEAttack.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAoE, Log);

UENUM()
enum class EAttackShape
{
	Circle	UMETA(Tooltip = "Calculated with a simple circle collision check"),
	Cone	UMETA(Tooltip = "Calculated using PointInTriangle."),
	Line	UMETA(Tooltip = "Calculated with 2D box encompass check"),
	Donut	UMETA(Tooltip = "Calculated with an inverse circle collision check.")
};

USTRUCT()
struct FAoEAttack
{
	GENERATED_BODY()

public:
	// Shape of the attack.
	UPROPERTY(EditAnywhere, Category = "Attack Settings|Shape")
	EAttackShape AttackShape;

	// Is the location relative to the boss?
	UPROPERTY(EditAnywhere, Category = "Attack Settings|Shape")
	bool bBossRelativePosition = true;

	// Location of this attack.
	UPROPERTY(EditAnywhere, Category = "Attack Settings|Shape")
	FVector AttackPosition = FVector::ZeroVector;

	// Where applicable, the "end" of the attack.
	UPROPERTY(EditAnywhere, Category = "Attack Settings|Shape")
	FVector AttackEnd = FVector::ZeroVector;

	// Radius or width (in cm) of the attack.
	UPROPERTY(EditAnywhere, Category = "Attack Settings|Shape")
	float Width = 50.f;

	// How much damage should be done by this attack?
	UPROPERTY(EditAnywhere, Category = "Attack Settings|Damage")
	float Damage = 1000.f;

	// If true, divide damage by the number of players hit and split it equally among them.
	UPROPERTY(EditAnywhere, Category = "Attack Settings|Damage")
	bool bIsSharedDamage = false;
	
	/* #TODO:
	* Some behaviors I'd like to try:
	* - Requiring players to soak the damage (having a fail condition)
	* - Snapshotting the direction/location of the AoE.
	*/
protected:

	bool SnapshotPlayers(TArray<ACharacter>& OutHitCharacters);
};
