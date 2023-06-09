/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ������ 1                                                                     */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include "Pawns/TIREnemyType01.h"
#include "Component/TIRTargetMovementComponent.h"
#include "Components/SphereComponent.h"

ATIREnemyType01::ATIREnemyType01(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetSizeEnemy(0.50f); // ������������� ������ ������ ������� ���� ������
	SetColorEnemy(FLinearColor::Red); // ������������� ���� ������� ���� ������
	GetMovementComponent()->SetSpeedMovement(250.0f); // ������������� �������� ������� ���� ������
	SetHealthMax(100.0f); // ������������� ������������ ���-�� �������� ������� ���� ������
	SetHealthCurrent(100.0f); // ������������� ������� ���-�� �������� ������� ���� ������
}