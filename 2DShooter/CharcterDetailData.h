#pragma once

class CharcterDetailData
{
private:
	double ASpeed[2];	//自身加速度 0-横轴 1-竖轴
	double MaxSpeed[3];	//最大速度 0-行走 1-冲刺 2-掉落
	double MaxForce[2];	//最大动力 0-行走 1-冲刺
	double Force[3];	//自身动力 0-行走 1-冲刺 2-跳跃

	double damp;//阻尼  加速度的递减
	double dampG;//阻尼	重力阻尼
	bool direction;//方向 False-向左  True-向右
	bool Towards;  //朝向 False-向左  True-向右

public:
	CharcterDetailData() :
		ASpeed{ 0,0 },
		MaxSpeed{3,10,15},
		MaxForce{3,10},
		dampG(0.15),
		damp(0.5)
	{
	}

	//一大堆的SET接口_(:D)∠)_

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

	//一大堆的GET接口:D

	//横坐标加速度
	double ASpeedX() { return ASpeed[0]; }

	//纵坐标加速度
	double ASpeedY() { return ASpeed[1]; }

	//掉落最大速度
	double MaxFallingSpeed() { return MaxSpeed[2]; }

	//行走最大速度
	double MaxForce1() { return MaxForce[0]; }

	//冲刺最大速度
	double MaxForce2() { return MaxForce[1]; }

	//行走动力
	double Force1() { return Force[0]; }

	//冲刺动力
	double Force2() { return Force[1]; }

	//跳跃动力
	double Force3() { return Force[2]; }

	//重力
	double DampG() { return dampG; }

	//横轴阻力
	double Damp() { return damp; }

	//方向	False-向左  True-向右
	bool Direction() { return direction; }
};