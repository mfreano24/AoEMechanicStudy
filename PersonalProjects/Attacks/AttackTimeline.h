// Michael Freaney, 2024
// michael.freaney324@gmail.com

#pragma once
#include "AttackSet.h"
#include "AttackTimeline.generated.h"

USTRUCT()
struct FTimelineEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Attack Settings")
	float Timestamp = 0.f;

	UPROPERTY(EditAnywhere, Category = "Attack Settings")
	FAttackSet AttackSet;
};

USTRUCT()
struct FAttackTimeline
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Attack Settings")
	TArray<FTimelineEvent> TimelineEvents;

	void Start(AActor* Owner);
	void Reset();
	void AdvanceTimeline(float DeltaTime = 0.f);
	float CurrTime = 0.f;

	bool bIsRunning = false;
	int32 Idx = 0;
};