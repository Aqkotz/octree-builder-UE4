// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Items/SOctreeBuilder.h"
#include "GameFramework/Actor.h"
#include "Octree.h"

AOctreebuilder::AOctreeBuilder()
{
}

static void AOctreeBuilder::subdivideOctree(Octree parent, int32 depth, float box_size, FVector CenterLocation)
{
	//subdivide on x axis
	for (int32 i = 0; i < 1; i++)
	{
		//subdivide on y axis
		for (int32 j = 0; j < 1; j++)
		{
			//subdivide on z axis
			for (int32 k = 0; k < 1; k++)
			{

				//spawn an octree actor
				float new_box_size = box_size / 2;
				FVector Location((new_box_size * (i - 0.5) + CenterLocation.x) f, (new_box_size * (j - 0.5) + CenterLocation.y) f, (new_box_size * (k - 0.5) + CenterLocation.z) f);
				FRotator Rotation(0.0f, 0.0f, 0.0f);
				FActorSpawnParameters SpawnInfo;
				Octree newOctree = GetWorld()->SpawnActor<Octree>(Location, Rotation, SpawnInfo, parent, box_size, Location);

				//check if our box is colliding
				FCollisionShape Shape = FCollisionShape::MakeBox(FVector(new_box_size, new_box_size, new_box_size));
				FHitResult SweepResult;
				bool Hit = GetWorld()->SweepSingleByChannel(SweepResult, Location, Location, Rotation, ECC_Visibility, Shape);

				//recurse if we haven't reached the bottom.
				if (depth >= 1 && Hit)
				{
					subdivideOctree(newOctree, depth - 1, new_box_size, Location);
				}
			}
		}
	}
};
