#include "Tools.h"
#include <math.h>

const double PI = 3.1415926535898;
const double PIUnder180 = 180.0 / PI;
const double PIOver180 = PI / 180.0;

double toRadians(double degrees)
{
	return degrees * PIOver180;
}
double toDegrees(double radians)
{
	return radians*PIUnder180;
}

bool LineLineCollision(D3DXVECTOR2 X1, D3DXVECTOR2 X2, D3DXVECTOR2 Y1, D3DXVECTOR2 Y2)
{
	////判断所需的两个变量
	//float uA = ((y2.x - y1.x)*(x1.y - y1.y) - (y2.y - y1.y)*(x1.x - y1.y)) / ((y2.y - y1.y)*(x2.x - x1.x) - (y2.y - y1.x)*(x2.y - x1.y));
	//float uB = ((x2.x - x1.x)*(x1.y - y1.y) - (x2.y - x1.y)*(x1.x - y1.x)) / ((y2.y - y1.y)*(x2.x - x1.x) - (y2.x - y1.x)*(x2.y - x1.y));
	float x1 = X1.x;
	float y1 = X1.y;
	float x2 = X2.x;
	float y2 = X2.y;
	float x3 = Y1.x;
	float y3 = Y1.y;
	float x4 = Y2.x;
	float y4 = Y2.y;

	float uA = ((x4 - x3)*(y1-y3) - (y4 - y3)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
	float uB = ((x2 - x1)*(y1-y3) - (y2 - y1)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));


	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) 
	{
		return true;
	}

	return false;
}
bool LineLineCollision(D3DXVECTOR2 X1, D3DXVECTOR2 X2, D3DXVECTOR2 Y1, D3DXVECTOR2 Y2, D3DXVECTOR2* inter)
{
	float x1 = X1.x;
	float y1 = X1.y;
	float x2 = X2.x;
	float y2 = X2.y;
	float x3 = Y1.x;
	float y3 = Y1.y;
	float x4 = Y2.x;
	float y4 = Y2.y;


	//判断所需的两个变量
	/*float uA = ((y2.x - y1.x)*(x1.y - y1.y) - (y2.y - y1.y)*(x1.x - y1.y)) / ((y2.y - y1.y)*(x2.x - x1.x) - (y2.y - y1.x)*(x2.y - x1.y));
	float uB = ((x2.x - x1.x)*(x1.y - y1.y) - (x2.y - x1.y)*(x1.x - y1.x)) / ((y2.y - y1.y)*(x2.x - x1.x) - (y2.x - y1.x)*(x2.y - x1.y));*/

	float uA = ((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
	float uB = ((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) 
	{
		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));

		inter->x = intersectionX;
		inter->y = intersectionY;

		return true;
	}

	return false;
}

bool LineRectCollision(D3DXVECTOR2 p1, D3DXVECTOR2 p2, RECT rect)
{
	D3DXVECTOR2 rectPoint1;
	D3DXVECTOR2 rectPoint2;


	//左侧
	rectPoint1.x = rect.left;rectPoint1.y = rect.top;
	rectPoint2.x = rect.left;rectPoint2.y = rect.bottom;
	bool left = LineLineCollision(p1, p2, rectPoint1, rectPoint2);

	//上测
	rectPoint1.x = rect.left;rectPoint1.y = rect.top;
	rectPoint2.x = rect.right;rectPoint2.y = rect.top;
	bool top = LineLineCollision(p1, p2, rectPoint1, rectPoint2);

	//右侧
	rectPoint1.x = rect.right;rectPoint1.y = rect.top;
	rectPoint2.x = rect.right;rectPoint2.y = rect.bottom;
	bool right = LineLineCollision(p1, p2, rectPoint1, rectPoint2);
	
	//底侧
	rectPoint1.x = rect.left;rectPoint1.y = rect.bottom;
	rectPoint2.x = rect.right;rectPoint2.y = rect.bottom;
	bool bottom = LineLineCollision(p1, p2, rectPoint1, rectPoint2);

	if (left || top || right || bottom)
	{
		return true;
	}

	return false;
}
bool LineRectCollision(D3DXVECTOR2 p1, D3DXVECTOR2 p2, RECT rect, D3DXVECTOR2 * pInter1)
{
	D3DXVECTOR2 rectPoint1;
	D3DXVECTOR2 rectPoint2;
	D3DXVECTOR2 interP1;
	D3DXVECTOR2 interP2;

	D3DXVECTOR2* p_interPoint = &interP1;

	//左侧
	rectPoint1.x = rect.left;rectPoint1.y = rect.top;
	rectPoint2.x = rect.left;rectPoint2.y = rect.bottom;
	bool left = LineLineCollision(p1, p2, rectPoint1, rectPoint2, p_interPoint);

	if (left) { p_interPoint = &interP2; }

	//上测
	rectPoint1.x = rect.left;rectPoint1.y = rect.top;
	rectPoint2.x = rect.right;rectPoint2.y = rect.top;
	bool top = LineLineCollision(p1, p2, rectPoint1, rectPoint2, p_interPoint);

	if (top) { p_interPoint = &interP2; }

	//右侧
	rectPoint1.x = rect.right;rectPoint1.y = rect.top;
	rectPoint2.x = rect.right;rectPoint2.y = rect.bottom;
	bool right = LineLineCollision(p1, p2, rectPoint1, rectPoint2, p_interPoint);

	if (right) { p_interPoint = &interP2; }

	//底侧
	rectPoint1.x = rect.left;rectPoint1.y = rect.bottom;
	rectPoint2.x = rect.right;rectPoint2.y = rect.bottom;
	bool bottom = LineLineCollision(p1, p2, rectPoint1, rectPoint2, p_interPoint);

	if (left || top || right || bottom)
	{
		if (interP2 == NULL)
		{
			*pInter1 = interP1;
		}
		else
		{
			//如果有两个碰撞点，比较大小，返回离射入点最近的
			float rang1 = abs((interP1.x - p1.x) + (interP1.y - p1.y));
			float rang2 = abs((interP2.x - p1.x) + (interP2.y - p1.y));
			if (rang1 < rang2)
			{
				*pInter1 = interP1;

			}
			else if (rang2 < rang1)
			{
				*pInter1 = interP2;
			}
		}
		return true;
	}

	return false;
}
bool LineRectCollision(D3DXVECTOR2 p1, D3DXVECTOR2 p2, RECT rect, D3DXVECTOR2 * pInter1, D3DXVECTOR2 * pInter2)
{
	D3DXVECTOR2 rectPoint1;
	D3DXVECTOR2 rectPoint2;
	D3DXVECTOR2 interP1;
	D3DXVECTOR2 interP2;

	D3DXVECTOR2* p_interPoint = &interP1;

	//左侧
	rectPoint1.x = rect.left;rectPoint1.y = rect.top;
	rectPoint2.x = rect.left;rectPoint2.y = rect.bottom;
	bool left = LineLineCollision(p1, p2, rectPoint1, rectPoint2, p_interPoint);

	if (left) { p_interPoint = &interP2; }

	//上测
	rectPoint1.x = rect.left;rectPoint1.y = rect.top;
	rectPoint2.x = rect.right;rectPoint2.y = rect.top;
	bool top = LineLineCollision(p1, p2, rectPoint1, rectPoint2, p_interPoint);

	if (top) { p_interPoint = &interP2; }

	//右侧
	rectPoint1.x = rect.right;rectPoint1.y = rect.top;
	rectPoint2.x = rect.right;rectPoint2.y = rect.bottom;
	bool right = LineLineCollision(p1, p2, rectPoint1, rectPoint2, p_interPoint);

	if (right) { p_interPoint = &interP2; }

	//底侧
	rectPoint1.x = rect.left;rectPoint1.y = rect.bottom;
	rectPoint2.x = rect.right;rectPoint2.y = rect.bottom;
	bool bottom = LineLineCollision(p1, p2, rectPoint1, rectPoint2, p_interPoint);
	
	if (left || top || right || bottom)
	{
		*pInter1 = interP1;
		*pInter2 = interP2;
		return true;
	}

	return false;
}

double getRadiansBytwoPoints(float x1, float y1, float x2, float y2)
{
	//建立一个三角形
	double x = x2 - x1;
	double y = y2 - y1;

	//三角形的斜边
	double h = sqrt(pow(x, 2) + pow(y, 2));

	//余弦
	double  cos = x / h;
	//弧度
	double radian = acos(cos);

	if (y < 0) radian = -radian;

	return radian;
}

double getRadiansBytwoPoints(D3DXVECTOR2 p1, D3DXVECTOR2 p2)
{
	return getRadiansBytwoPoints(p1.x,p1.y,p2.x,p2.y);
}


double GetMouseAngle()
{
	return 0.0;
}