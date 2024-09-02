// Michael Freaney, 2024
// michael.freaney324@gmail.com

#include "HelperLibrary.h"

float UHelperLibrary::AreaTriangle(const FVector& A, const FVector& B, const FVector& C)
{
	return FMath::Abs((A.X * (B.Y- C.Y) + B.X * (C.Y - A.Y) + C.X * (A.Y - B.Y)) / 2.0);
}