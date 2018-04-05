#include "Charcter.h"

C_Normal* C_Normal::Instance()
{
	static C_Normal instance;
	return &instance;
}
void C_Normal::SetCharcterData(Charcter* pCharcter)
{
	CharcterDetailData* pData= pCharcter->GetDetailData();

	pCharcter->SetHealth(100);

	pData->SetDamp(0.15);
	pData->SetDampG(0.070);
	pData->SetMaxForce(3, 5);
	pData->SetForce(0.75, 10, -6.5);
}

C_Fast* C_Fast::Instance()
{
	static C_Fast instance;
	return &instance;
}
void C_Fast::SetCharcterData(Charcter* pCharcter)
{

}

C_Heavy* C_Heavy::Instance()
{
	static C_Heavy instance;
	return &instance;
}
void C_Heavy::SetCharcterData(Charcter* pCharcter)
{
	
}