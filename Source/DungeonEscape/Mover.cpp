// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	float MyFloat = 10.0f;
	float* MyFloatPointer = &MyFloat;

	float Result = *MyFloatPointer + 10.0f;
	UE_LOG(LogTemp, Display, TEXT("Result: %f"), Result);

	*MyFloatPointer = 30.0f;
	UE_LOG(LogTemp, Display, TEXT("MyFloat: %f"), MyFloat);
	UE_LOG(LogTemp, Display, TEXT("MyFloatPointer: %f"), *MyFloatPointer);
	UE_LOG(LogTemp, Display, TEXT("MyFloatPointer: %p"), MyFloatPointer);
	UE_LOG(LogTemp, Display, TEXT("MyFloatPointer: %p"), &MyFloat);

	// ------

	FVector MyVector(1.0f, 2.0f, 3.0f);
	FVector* MyVectorPointer = &MyVector;

	MyVectorPointer->X = 10.0f;
	MyVectorPointer->Y = 20.0f;
	MyVectorPointer->Z = 30.0f;

	UE_LOG(LogTemp, Display, TEXT("MyVector: %s"), *MyVector.ToString());
	UE_LOG(LogTemp, Display, TEXT("MyVectorPointer: %p"), MyVectorPointer);

}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

