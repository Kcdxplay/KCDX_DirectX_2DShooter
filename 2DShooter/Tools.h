#pragma once
#include "DirectX.h"

double toRadians(double degrees);//�Ƕ�ת����
double toDegrees(double radians);//����ת�Ƕ�

//��-����ײ���
bool LineLineCollision(D3DXVECTOR2 X1, D3DXVECTOR2 X2, D3DXVECTOR2 Y1, D3DXVECTOR2 Y2);
//��-����ײ��⣬���ؽ����
bool LineLineCollision(D3DXVECTOR2 X1, D3DXVECTOR2 X2, D3DXVECTOR2 Y1, D3DXVECTOR2 Y2, D3DXVECTOR2* inter);

//��-������ײ���
bool LineRectCollision(D3DXVECTOR2 p1, D3DXVECTOR2 p2, RECT rect);
//��-������ײ��⣬���ص�һ�������
bool LineRectCollision(D3DXVECTOR2 p1, D3DXVECTOR2 p2, RECT rect, D3DXVECTOR2* pInter1);
//��-������ײ��⣬�������������
bool LineRectCollision(D3DXVECTOR2 p1, D3DXVECTOR2 p2, RECT rect, D3DXVECTOR2* pInter1, D3DXVECTOR2* pInter2);

//��ȡ��һ�����Ӧ�ڶ����㣬�����X�����ת�Ƕȡ������ȣ�
double getRadiansBytwoPoints(float x1, float y1, float x2, float y2);
double getRadiansBytwoPoints(D3DXVECTOR2 p1, D3DXVECTOR2 p2);


//��ȡ�����Ӧ������תλ�ã����ȣ�
double GetMouseAngle();