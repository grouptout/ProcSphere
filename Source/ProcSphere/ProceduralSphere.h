// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralSphere.generated.h"

UCLASS(Blueprintable)
class PROCSPHERE_API AProceduralSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
    void BuildUVSphere(const int Slices, const int Stacks, const float Radius, TArray<FVector>& SphereVertices, TArray<int32>& SphereTriangles);
    	
    UFUNCTION(BlueprintCallable)
    void GenerateUVs(const TArray<FVector>& SphereVertices, TArray<FVector2D>& SphereUVs);

};
