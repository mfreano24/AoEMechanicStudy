// Michael Freaney, 2024
// michael.freaney324@gmail.com

#pragma once
#include "AttackTimeline.h"
#include "BossFightController.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ABossFightController : public AActor
{
	GENERATED_BODY()

protected:
	ABossFightController();
	// AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Boss Fight")
	void StartFight();

	UPROPERTY(EditAnywhere, Category = "Boss Fight")
	FAttackTimeline Timeline;

protected:
	// Components
	UPROPERTY()
	class USceneComponent* SceneComponent;

	UPROPERTY()
	class USkeletalMeshComponent* SkelmeshComponent;
};