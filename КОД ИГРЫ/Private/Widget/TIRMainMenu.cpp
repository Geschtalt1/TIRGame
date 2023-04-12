/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                       ВИДЖЕТ ГЛАВНОГО МЕНЮ                                                                */
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

	/* Зайти на уровень */
	B_Play->OnClicked.AddDynamic(this, &UTIRMainMenu::OnPlayGame);

	/* Выйти из игры*/
	B_Exit->OnClicked.AddDynamic(this, &UTIRMainMenu::OnExitGame);
}

/* Играть */
void UTIRMainMenu::OnPlayGame()
{
	// Перед заходом на уровень, стираем виджет
	UTIRHelperLibrary::SetWidgetGame(nullptr, nullptr, this);

	// Настройки игры,одна минута по дефолту (устанаовлена в гейм моде), кол-во врагов зайдается случайным образом от 5 до 15
	const int32 Random = UKismetMathLibrary::RandomIntegerInRange(5, 15);
	int32 Time = 0;
	
	// Если врагов от 10 и больше добавляем одну минуту к игре
	if (Random >= 10)
		Time = 1;

	UTIRHelperLibrary::SetGameSetting(UGameplayStatics::GetGameInstance(GetWorld()), Time, Random);

	// Запускаем уровень
	UGameplayStatics::OpenLevel(GetWorld(), FName(GameLevel));
}

/* Выйти с игры */
void UTIRMainMenu::OnExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}
