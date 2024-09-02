// Michael Freaney, 2024
// michael.freaney324@gmail.com

#include "BossFightController.h"

ABossFightController::ABossFightController()
	: Super()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	SkelmeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkelmeshComponent"));
	SkelmeshComponent->SetupAttachment(SceneComponent);

	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);
}

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
