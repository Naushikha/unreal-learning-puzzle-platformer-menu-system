// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true; // This is appparently required for every C++ actor !READ!
	SetMobility(EComponentMobility::Movable);
}

// This bit of code makes sure that the server propogates down the replication to the client
void AMovingPlatform::BeginPlay() {
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
		// Do some pre-calculations
		GlobalStartLocation = GetActorLocation();
		GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation); // TargetLocation is local to this actor (relative to its origin)
		GlobalJourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size(); // Get the magnitude (length) of the vector
		UpdateUnitMoveDirection();
	}
}

void AMovingPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	// Available on the actor, TRUE means server
	if (HasAuthority() && ActiveTriggers) {
		FVector Location = GetActorLocation();
		Location += UnitMoveDirection * Speed * DeltaTime;
		SetActorLocation(Location);
		float JourneyTravelled = (GlobalStartLocation - Location).Size();
		if (JourneyTravelled >= GlobalJourneyLength) {
			MoveInOppositeDirection();
		}
	}
}

void AMovingPlatform::UpdateUnitMoveDirection() {
	UnitMoveDirection = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
}

void AMovingPlatform::MoveInOppositeDirection() {
	FVector Swap = GlobalStartLocation;
	GlobalStartLocation = GlobalTargetLocation;
	GlobalTargetLocation = Swap;
	UpdateUnitMoveDirection();
}

void AMovingPlatform::AddActiveTrigger() { ActiveTriggers++; }
void AMovingPlatform::RemoveActiveTrigger() { if (ActiveTriggers) ActiveTriggers--; }