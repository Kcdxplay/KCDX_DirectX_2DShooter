#include "Charcter.h"


CharcterDetailData * Charcter::GetDetailData()
{
	return &data;
}
Graphic * Charcter::GetGraphic()
{
	return &graph;
}
list<Bullet>* Charcter::Bullets()
{
	return &bullets;
}
float Charcter::Health()
{
	return this->health;
}

//设置各个具体数据

void CharcterDetailData::SetASpeed(double ASpeed[2])
{
	memcpy(this->ASpeed, ASpeed, sizeof(this->ASpeed));
}
void CharcterDetailData::SetASpeed(double AS1, double AS2)
{
	ASpeed[0] = AS1;
	ASpeed[1] = AS2;
}
void CharcterDetailData::SetMaxForce(double MaxForce[2])
{
	memcpy(this->MaxForce, MaxForce, sizeof(this->MaxForce));
}
void CharcterDetailData::SetMaxForce(double MF1, double MF2)
{
	this->MaxForce[0] = MF1;
	this->MaxForce[1] = MF2;
}
void CharcterDetailData::SetForce(double Force[3])
{
	memcpy(this->Force, Force, sizeof(this->Force));
}
void CharcterDetailData::SetForce(double F1, double F2, double F3)
{
	Force[0] = F1;
	Force[1] = F2;
	Force[2] = F3;
}
void CharcterDetailData::SetDamp(double damp)
{
	this->damp = damp;
}
void CharcterDetailData::SetDampG(double dampG)
{
	this->dampG = dampG;
}
void CharcterDetailData::SetDirection(bool direction)
{
	this->direction = direction;
}

void CharcterDetailData::SetASpeedX(double ASpeedX)
{
	this->ASpeed[0] = ASpeedX;
}
void CharcterDetailData::SetASpeedY(double ASpeedY)
{
	this->ASpeed[1] = ASpeedY;
}