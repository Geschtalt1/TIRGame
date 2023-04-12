// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TIREnemyType03.h"
#include "Component/TIRTargetMovementComponent.h"
#include "Components/WidgetComponent.h"

ATIREnemyType03::ATIREnemyType03(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetSizeEnemy(0.70f); // ������������� ������ ������� ���� ������
	SetColorEnemy(FLinearColor::Blue); // ������������� ���� ������� ���� ������
	GetMovementComponent()->SetSpeedMovement(500.0f); // ������������� �������� ������� ���� ������
	SetHealthMax(300.0f); // ������������� ������������ ���-�� �������� ������� ���� ������
	SetHealthCurrent(300.0f); // ������������� ������� ���-�� �������� ������� ���� ������
	HealthWidgetComponent->SetWorldLocation(FVector(75.0, 0.0, 0.0)); // ������������� ������ ������� ��������
}
