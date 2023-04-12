// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TIREnemyType03.h"
#include "Component/TIRTargetMovementComponent.h"
#include "Components/WidgetComponent.h"

ATIREnemyType03::ATIREnemyType03(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetSizeEnemy(0.70f); // Устанавливаем размер третему типу мишени
	SetColorEnemy(FLinearColor::Blue); // Устанавливаем цвет третему типу мишени
	GetMovementComponent()->SetSpeedMovement(500.0f); // Устанавливаем скорость третему типу мишени
	SetHealthMax(300.0f); // Устанавливаем максимальное кол-во здоровья третему типу мишени
	SetHealthCurrent(300.0f); // Устанавливаем текущее кол-во здоровья третему типу мишени
	HealthWidgetComponent->SetWorldLocation(FVector(75.0, 0.0, 0.0)); // Устанавливаем высоту виджета здоровья
}
