// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralSphere.h"

// Sets default values
AProceduralSphere::AProceduralSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProceduralSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProceduralSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProceduralSphere::BuildUVSphere(const int Slices, const int Stacks, const float Radius, TArray<FVector>& SphereVertices, TArray<int32>& SphereTriangles)
{
	SphereVertices.Empty();
	SphereTriangles.Empty();
	
	// add top vertex
	auto v0 = SphereVertices.Add(FVector(0, Radius, 0));

	// generate vertices per stack / slice
	for (int32 i = 0; i < Stacks - 1; i++)
	{
		auto phi = PI * double(i + 1) / double(Stacks);
		for (int32 j = 0; j < Slices; j++)
		{
			auto theta = 2.0 * PI * double(j) / double(Slices);
			auto x = FMath::Sin(phi) * FMath::Cos(theta);
			auto y = FMath::Cos(phi);
			auto z = FMath::Sin(phi) * FMath::Sin(theta);
			SphereVertices.Add(FVector(x * Radius, y * Radius, z * Radius));
		}
	}
	
	// add bottom vertex
	auto v1 = SphereVertices.Add(FVector(0, -Radius, 0));

	// add top / bottom triangles
	for (int32 i = 0; i < Slices; ++i)
	{
		auto i0 = i + 1;
		auto i1 = (i + 1) % Slices + 1;

		SphereTriangles.Add(i0);
		SphereTriangles.Add(i1);
		SphereTriangles.Add(v0);
		
		i0 = i + Slices * (Stacks - 2) + 1;
		i1 = (i + 1) % Slices + Slices * (Stacks - 2) + 1;

		SphereTriangles.Add(i1);
		SphereTriangles.Add(i0);
		SphereTriangles.Add(v1);
	}

	// add quads per stack / slice
	for (int32 j = 0; j < Stacks - 2; j++)
	{
		auto j0 = j * Slices + 1;
		auto j1 = (j + 1) * Slices + 1;
		for (int i = 0; i < Slices; i++)
		{
			auto i0 = j0 + i;
			auto i1 = j0 + (i + 1) % Slices;
			auto i2 = j1 + (i + 1) % Slices;
			auto i3 = j1 + i;
			
			SphereTriangles.Add(i0);
			SphereTriangles.Add(i3);
			SphereTriangles.Add(i2);
			
			SphereTriangles.Add(i2);
			SphereTriangles.Add(i1);
			SphereTriangles.Add(i0);	
		}
	}
}

void AProceduralSphere::GenerateUVs(const int Slices, const int Stacks, const TArray<FVector>& SphereVertices, TArray<FVector2D>& SphereUVs)
{
	const auto textureCellsCount = 16;    
	const auto uvXStep = 1.f / Slices;
	const auto uvYStep = 1.f / Stacks;
 
	auto uvX = 0.f;
	auto uvY = 0.f;
 
	// add top vertex
	SphereUVs.Add(FVector2D(0, 0.5f));
 
	// generate vertices per stack / slice
	for (int32 i = 0; i < Stacks - 1; i++) {
		uvX = 0;
		uvY += uvYStep;
         
		for (int32 j = 0; j < Slices; j++) {
			uvX += uvXStep;
			SphereUVs.Add(FVector2D(uvX, uvY));
		}
	}
 
	// add bottom vertex
	SphereUVs.Add(FVector2D(1, 0.5f));
}
