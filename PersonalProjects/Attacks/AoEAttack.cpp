// Michael Freaney, 2024
// michael.freaney324@gmail.com

#include "AoEAttack.h"
#include "GameFramework/Character.h"
#include "PersonalProjects/Globals/HelperLibrary.h"

DEFINE_LOG_CATEGORY(LogAoE);

namespace Attacks
{
	static float FLT_INF = 999999.999f; //TODO: make this the edge of the arena?

	bool TestCharacter_Circle(const FVector& Center, const float Radius, const ACharacter* Character)
	{
		return FVector::DistSquared2D(Center, Character->GetActorLocation()) <= (Radius * Radius);
	}

	bool TestCharacter_Cone(const FVector& Origin, const FVector& End, const float Width, const ACharacter* Character)
	{
		// construct conal triangle:
		/*
	   ------- -> (End + RightDir * 0.5f * Width)
		\ | /
		 \|/
		  v - Origin
		*/

		const FVector ConalEnd = (End == FVector::ZeroVector) ? FVector(FLT_INF) : End;
		FVector RightDir = ConalEnd - Origin;
		RightDir.Y = -RightDir.Y;
		const float Temp = RightDir.X;
		RightDir.X = RightDir.Y;
		RightDir.Y = Temp;
		RightDir.Normalize();

		const FVector B = ConalEnd + (0.5f * Width * RightDir);
		const FVector C = ConalEnd - (0.5f * Width * RightDir);

		// Use area method
		const float TriArea = UHelperLibrary::AreaTriangle(Origin, B, C);
		const float A1 = UHelperLibrary::AreaTriangle(Character->GetActorLocation(), B, C);
		const float A2 = UHelperLibrary::AreaTriangle(Origin, Character->GetActorLocation(), C);
		const float A3 = UHelperLibrary::AreaTriangle(Origin, B, Character->GetActorLocation());

		return FMath::Abs((A1 + A2 + A3) - TriArea) <= 0.05f;
	}

	bool TestCharacter_Line(const FVector& Start, const FVector& End, const float Width, const ACharacter* Character)
	{
		const float XMin = FMath::Min(Start.X, End.X), XMax = FMath::Max(Start.X, End.X);
		const float YMin = FMath::Min(Start.Y, End.Y), YMax = FMath::Max(Start.Y, End.Y);

		const FVector Loc = Character->GetActorLocation();
		return Loc.X <= XMax && Loc.X >= XMin && Loc.Y <= YMax && Loc.Y >= YMin;
	}
};

bool FAoEAttack::SnapshotPlayers(TArray<ACharacter*>& ExistingCharacters, TArray<ACharacter*>& OutHitCharacters)
{
	if (!OwnerPtr.IsValid())
	{
		return false;
	}

	FVector Loc = bBossRelativePosition ? OwnerPtr->GetActorLocation() + AttackPosition : AttackPosition;
	for (ACharacter* Character : ExistingCharacters)
	{
		FString AttackShapeName;
		switch (AttackShape)
		{
		case EAttackShape::Circle:
			if (Attacks::TestCharacter_Circle(Loc, Width, Character))
			{
				OutHitCharacters.Add(Character);
			}
			break;
		case EAttackShape::Cone:
			if (Attacks::TestCharacter_Cone(Loc, Loc + Width * OwnerPtr->GetActorForwardVector(), Width, Character)) //#TODO: get arena size or something for Forward vec
			{
				OutHitCharacters.Add(Character);
			}
			break;
		case EAttackShape::Line:
			if (Attacks::TestCharacter_Line(Loc, Loc + Width * OwnerPtr->GetActorForwardVector(), Width, Character)) //#TODO: get arena size or something for Forward vec
			{
				OutHitCharacters.Add(Character);
			}
			break;
		case EAttackShape::Donut:
			if (!Attacks::TestCharacter_Circle(Loc, Width, Character))
			{
				OutHitCharacters.Add(Character);
			}
			break;
		default:
			if (StaticEnum<EAttackShape>()->FindNameStringByValue(AttackShapeName, (uint64)AttackShape))
			{
				UE_LOG(LogAoE, Warning, TEXT("Unimplemented attack shape requested: [%s]"), *AttackShapeName);
			}
			break;
		}
	}

	return OutHitCharacters.Num() > 0;
}
