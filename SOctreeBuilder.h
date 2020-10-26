// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SOctreeBuilder.generated.h"
#include "Octree"

/**
 * 
 */
UCLASS()
class SOctreeBuilder : public AActor
{
	GENERATED_BODY()

public:
	octreeBuilder();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "default")
	int32 octreeDepth;

	UFUNCTION(BlueprintCallable, category = "default")
	void subdivideOctree();

protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
