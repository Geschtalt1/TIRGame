// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TIRResultWidget.h"
#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"
#include "Library/TIRHelperLibrary.h"

void UTIRResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/* ������������� �����*/
	B_Restart->OnClicked.AddDynamic(this, &UTIRResultWidget::OnRestart);

	/* ����� � ���� ����*/
	B_Exit->OnClicked.AddDynamic(this, &UTIRResultWidget::OnExitMenu);
}

/* ������� ������*/
void UTIRResultWidget::OnRestart()
{
	/* ������������� �������*/
	UTIRHelperLibrary::SetWidgetGame(nullptr, nullptr, this); // ������� ������
	UGameplayStatics::OpenLevel(this, FName("Level_01")); // ������������� �������
}

/* ����� � ���� ���� */
void UTIRResultWidget::OnExitMenu()
{
	UTIRHelperLibrary::SetWidgetGame(nullptr, nullptr, this); // ������� ������
	UGameplayStatics::OpenLevel(this, Menu); // �������� ������� ����
}