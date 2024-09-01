// Michael Freaney, 2024
// michael.freaney324@gmail.com

#include "AoEAttack.h"
#include "GameFramework/Character.h"

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
		FVector RightDir = End - Origin;
		RightDir.Y = -RightDir.Y;
		float Temp = RightDir.X;
		RightDir.X = RightDir.Y;
		RightDir.Y = Temp;
		RightDir.Normalize();

		const FVector B = End + (0.5f * Width * RightDir);
		const FVector C = End - (0.5f * Width * RightDir);

		//#TODO: check character is in triangle we just made
		
	}

	bool TestCharacter_Line(const FVector& Start, const FVector& End, const float Width, const ACharacter* Character)
	{
		const float XMin = FMath::Min(Start.X, End.X), XMax = FMath::Max(Start.X, End.X);
		const float YMin = FMath::Min(Start.Y, End.Y), YMax = FMath::Max(Start.Y, End.Y);

		const FVector Loc = Character->GetActorLocation();
		return Loc.X <= XMax && Loc.X >= XMin && Loc.Y <= YMax && Loc.Y >= YMin;
	}
};

bool FAoEAttack::SnapshotPlayers(TArray<ACharacter>& OutHitCharacters)
{

	switch (AttackShape)
	{
	case EAttackShape::Circle:
		break;
	case EAttackShape::Cone:
		break;
	case EAttackShape::Line:
		break;
	case EAttackShape::Donut:
		break;
	default:
		
	}
}
