// Michael Freaney, 2024
// michael.freaney324@gmail.com

#pragma once
#include "AttackTimeline.h"

void FAttackTimeline::Start(AActor* Owner)
{
	Reset();
	bIsRunning = true;

	for (FTimelineEvent& TimelineEvent : TimelineEvents)
	{
		TimelineEvent.AttackSet.Init(Owner);
	}
}

void FAttackTimeline::Reset()
{
	CurrTime = 0.f;
	Idx = 0;
}

void FAttackTimeline::AdvanceTimeline(float DeltaTime /*= 0.f*/)
{
	CurrTime += DeltaTime;
	
	if (CurrTime >= TimelineEvents[Idx].Timestamp)
	{
		TimelineEvents[Idx].AttackSet.Start();
		Idx++;
	}
}