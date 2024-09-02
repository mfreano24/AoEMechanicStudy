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
	int32 Timestamp = 0;

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
protected:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Attack Settings", meta=(UIMin=0, UIMax = 600, ClampMin = 0, ClampMax = 600))
	int32 PreviewTimestamp = 0.f;
#endif
};