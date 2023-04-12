/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                       ������ �������� ����                                                                */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include "Widget/TIRMainMenu.h"

#include "TIRGameInstance.h"

#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Library/TIRHelperLibrary.h"

void UTIRMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	/* ����� �� ������� */
	B_Play->OnClicked.AddDynamic(this, &UTIRMainMenu::OnPlayGame);

	/* ����� �� ����*/
	B_Exit->OnClicked.AddDynamic(this, &UTIRMainMenu::OnExitGame);
}

/* ������ */
void UTIRMainMenu::OnPlayGame()
{
	// ����� ������� �� �������, ������� ������
	UTIRHelperLibrary::SetWidgetGame(nullptr, nullptr, this);

	// ��������� ����,���� ������ �� ������� (������������ � ���� ����), ���-�� ������ ��������� ��������� ������� �� 5 �� 15
	const int32 Random = UKismetMathLibrary::RandomIntegerInRange(5, 15);
	int32 Time = 0;
	
	// ���� ������ �� 10 � ������ ��������� ���� ������ � ����
	if (Random >= 10)
		Time = 1;

	UTIRHelperLibrary::SetGameSetting(UGameplayStatics::GetGameInstance(GetWorld()), Time, Random);

	// ��������� �������
	UGameplayStatics::OpenLevel(GetWorld(), FName(GameLevel));
}

/* ����� � ���� */
void UTIRMainMenu::OnExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}
