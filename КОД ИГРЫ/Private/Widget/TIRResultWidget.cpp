// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TIRResultWidget.h"
#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"
#include "Library/TIRHelperLibrary.h"

void UTIRResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/* Перезапустить левел*/
	B_Restart->OnClicked.AddDynamic(this, &UTIRResultWidget::OnRestart);

	/* Выйти в меню игры*/
	B_Exit->OnClicked.AddDynamic(this, &UTIRResultWidget::OnExitMenu);
}

/* Рестарт уровня*/
void UTIRResultWidget::OnRestart()
{
	/* Перезапускаем уровень*/
	UTIRHelperLibrary::SetWidgetGame(nullptr, nullptr, this); // Удаляем виджет
	UGameplayStatics::OpenLevel(this, FName("Level_01")); // Перезапускаем уровень
}

/* Выйти в меню игры */
void UTIRResultWidget::OnExitMenu()
{
	UTIRHelperLibrary::SetWidgetGame(nullptr, nullptr, this); // Удаляем виджет
	UGameplayStatics::OpenLevel(this, Menu); // Включаем уровень меню
}