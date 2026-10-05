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
            UE_LOG(LogTemp, Warning, TEXT("%s: Mover component not found on MoverActor"), *GetOwner()->GetActorNameOrLabel());
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: MoverActor is nullptr"), *GetOwner()->GetActorNameOrLabel());
    }

    if (IsPressurePlate)
    {
        OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
        OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
    }
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTriggerComponent::Trigger(bool NewTriggerValue)
{
    isTriggered = NewTriggerValue;

    if (Mover)
        {
            Mover->SetShouldMove(isTriggered);
        }
    else
        {
        UE_LOG(LogTemp, Warning, TEXT("%s: Mover is nullptr"), *GetOwner()->GetActorNameOrLabel());
        }
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
    {
        if (!isTriggered)
        {
            Trigger(true);
        }
    }

}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
    {
       if (isTriggered)
        {
            Trigger(false);
        }
    }

}
