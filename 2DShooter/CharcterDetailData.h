#pragma once

class CharcterDetailData
{
private:
	double ASpeed[2];	//������ٶ� 0-���� 1-����
	double MaxSpeed[3];	//����ٶ� 0-���� 1-��� 2-����
	double MaxForce[2];	//����� 0-���� 1-���
	double Force[3];	//������ 0-���� 1-��� 2-��Ծ

	double damp;//����  ���ٶȵĵݼ�
	double dampG;//����	��������
	bool direction;//���� False-����  True-����
	bool Towards;  //���� False-����  True-����

public:
	CharcterDetailData() :
		ASpeed{ 0,0 },
		MaxSpeed{3,10,15},
		MaxForce{3,10},
		dampG(0.15),
		damp(0.5)
	{
	}

	//һ��ѵ�SET�ӿ�_(:D)��)_

	void SetASpeed(double ASpeed[2]);
	void SetASpeed(double AS1, double AS2);
	void SetMaxSpeed(double MaxSpeed[3]);
	void SetMaxSpeed(double M1, double M2, double M3);
	void SetMaxForce(double MaxForce[2]);
	void SetMaxForce(double MF1, double MF2);
	void SetForce(double Force[3]);
	void SetForce(double F1, double F2, double F3);
	void SetDampG(double dampG);
	void SetDamp(double damp);
	void SetDirection(bool direction);

	void SetASpeedX(double ASpeedX);
	void SetASpeedY(double ASpeedY);

	//һ��ѵ�GET�ӿ�:D

	//��������ٶ�
	double ASpeedX() { return ASpeed[0]; }

	//��������ٶ�
	double ASpeedY() { return ASpeed[1]; }

	//��������ٶ�
	double MaxFallingSpeed() { return MaxSpeed[2]; }

	//��������ٶ�
	double MaxForce1() { return MaxForce[0]; }

	//�������ٶ�
	double MaxForce2() { return MaxForce[1]; }

	//���߶���
	double Force1() { return Force[0]; }

	//��̶���
	double Force2() { return Force[1]; }

	//��Ծ����
	double Force3() { return Force[2]; }

	//����
	double DampG() { return dampG; }

	//��������
	double Damp() { return damp; }

	//����	False-����  True-����
	bool Direction() { return direction; }
};