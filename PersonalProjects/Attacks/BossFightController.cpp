// Michael Freaney, 2024
// michael.freaney324@gmail.com

#include "BossFightController.h"

void ABossFightController::BeginPlay()
{
	Super::BeginPlay();
}

void ABossFightController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABossFightController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Timeline.bIsRunning)
	{
		Timeline.AdvanceTimeline(DeltaTime);
	}
}

void ABossFightController::StartFight()
{
	Timeline.Start(this);
}
