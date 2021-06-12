﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BatteryManager.generated.h"

class ABattery;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEnergyChangedSignature, float, float)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GMTK_2021_API UBatteryManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UBatteryManager();

protected:
	virtual void BeginPlay() override;

	// Energy
public:
	float GetEnergy() const { return Energy; }
	float GetMaxEnergy() const { return MaxEnergy; }
	float GetNormalizedEnergy() const { return Energy / MaxEnergy; }
	void SetDecreaseRate(const float NewRate);
	void SetIncreaseRate(const float NewRate);
	bool IncreaseEnergy(const float DeltaEnergy);
	bool DecreaseEnergy(const float DeltaEnergy);
	FOnEnergyChangedSignature OnEnergyChanged;

private:
	UPROPERTY(VisibleAnywhere, Category="Energy")
	float Energy = 100.f;
	UPROPERTY(EditDefaultsOnly, Category="Energy", meta=(AllowPrivateAccess="true", ClampMin="0.0"))
	float MaxEnergy = 100.f;
	UPROPERTY(EditDefaultsOnly, Category="Energy", meta=(AllowPrivateAccess="true", ClampMin="0.0"))
	float DecreaseRate = 1.f;
	float DecreaseInterval = 1.f;
	UPROPERTY(EditDefaultsOnly, Category="Energy", meta=(AllowPrivateAccess="true", ClampMin="0.0"))
	float IncreaseRate = 1.f;
	float IncreaseInterval = 1.f;

// Battery
public:
	UPROPERTY(EditDefaultsOnly, Category="Battery")
	TSubclassOf<ABattery> BatteryClass = nullptr;
	ABattery* GetBatteryActor() const { return BatteryActor; }
	
	void EquipBattery();
	void UnequipBattery(USkeletalMeshComponent* SkeletalMesh);
private:
	UPROPERTY(EditDefaultsOnly, Category="Battery")
	FName BatterySocketName = "BatterySocket";
	UPROPERTY()
	ABattery* BatteryActor = nullptr;

	void SpawnBattery();
	void AttachBatteryToSocket(USkeletalMeshComponent* SkeletalMesh, const FName SocketName);
};
