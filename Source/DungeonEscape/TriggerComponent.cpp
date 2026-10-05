// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (MoverActor)
    {
        Mover = MoverActor->GetComponentByClass<UMover>();
        if (!Mover)
        {
            UE_LOG(LogTemp, Warning, TEXT("Mover component not found on MoverActor"));
        }
        else 
        {
            UE_LOG(LogTemp, Warning, TEXT("Mover component found on MoverActor"));
            Mover->ShouldMove = true;
        }
    }
    else 
    {
        UE_LOG(LogTemp, Warning, TEXT("MoverActor is nullptr"));
    }

    if (IsPressurePlate)
    {
        OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
        OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
    }
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->ActorHasTag("PressurePlateActivator"))
    {
      if (Mover)
        {
             Mover->ShouldMove = true;
        }
    }

}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor->ActorHasTag("PressurePlateActivator"))
    {
        if (Mover)
        {
            Mover->ShouldMove = false;
        }
    }

}
