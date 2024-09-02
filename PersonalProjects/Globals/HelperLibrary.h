// Michael Freaney, 2024
// michael.freaney324@gmail.com

#pragma once

class UHelperLibrary
{
public:
	// Calculates the area of a triangle made of 3 points (A, B, and C). Assumes 2D and uses X/Y only.
	static float AreaTriangle(const FVector& A, const FVector& B, const FVector& C);
};