// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 *
 */
UCLASS()
class PUZZLEPLATFORMER_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AMovingPlatform();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnyWhere)
		float Speed = 20;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true)) // Gizmo FVector Property
		FVector TargetLocation;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

private:
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
	float GlobalJourneyLength;
	FVector UnitMoveDirection;
	void UpdateUnitMoveDirection();
	void MoveInOppositeDirection();

	UPROPERTY(EditAnywhere)
		int ActiveTriggers = 1;
};
