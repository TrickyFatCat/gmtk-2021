﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Triggers/EnergyTrigger.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "EnergyZone.generated.h"

UENUM(BlueprintType)
enum class EZoneState : uint8
{
	Active,
	Inactive,
	Transition
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZoneChangeStateSignature, EZoneState, NewState);

UCLASS()
class GMTK_2021_API AEnergyZone : public AActor
{
	GENERATED_BODY()

public:
	AEnergyZone();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category="EnergyZone")
	bool ActivateZone();
	UFUNCTION(BlueprintCallable, Category="EnergyZone")
	bool DeactivateZone();

	// Components
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UEnergyTrigger* EnergyTrigger = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* ZoneEffect = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UTimelineComponent* AnimationTimeline = nullptr;

	// States
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnergyZone")
	EZoneState InitialState = EZoneState::Inactive;
	UFUNCTION(BlueprintPure, Category="EnergyZone")
	bool IsCurrentState(const EZoneState State) const { return CurrentState == State; }
	UFUNCTION(BlueprintImplementableEvent, Category="EnergyZone")
	void OnStateChanged(const EZoneState NewState);
	UPROPERTY(BlueprintAssignable, Category="EnergyZone")
	FOnZoneChangeStateSignature OnChangeState;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="EnergyZone", meta=(AllowPrivateAccess="true"))
	bool bIsIncreasingEnergy = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EnergyZone", meta=(AllowPrivateAccess="true"))
	EZoneState CurrentState = EZoneState::Inactive;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EnergyZone", meta=(AllowPrivateAccess="true"))
	EZoneState TargetState = EZoneState::Inactive;
	void ChangeState(const EZoneState NewState);

	// Animation
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	UCurveFloat* AnimationCurve = nullptr;
	UFUNCTION(BlueprintGetter)
	float GetAnimationDuration() const { return AnimationDuration; }
	UFUNCTION(BlueprintSetter)
	void SetAnimationDuration(const float NewDuration);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	FVector TargetScale = FVector(1.f, 1.f, 1.f);
private:
	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetAnimationDuration, BlueprintSetter=SetAnimationDuration, Category="Animation", meta=(AllowPrivateAccess="true"))
	float AnimationDuration = 0.25f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Animation", meta=(AllowPrivateAccess="true"))
	FVector InitialScale = FVector::ZeroVector;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Animation", meta=(AllowPrivateAccess="true"))
	FVector NewScale = FVector::ZeroVector;
	void CalculatePlayRate() const;
	void StartTransition();
	UFUNCTION()
	void SetZoneScale(const float Progress);
	UFUNCTION()
	void FinishTransition();
	
};
