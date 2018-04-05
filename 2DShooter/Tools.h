#pragma once
#include "DirectX.h"

double toRadians(double degrees);//角度转弧度
double toDegrees(double radians);//弧度转角度

//线-线碰撞检测
bool LineLineCollision(D3DXVECTOR2 X1, D3DXVECTOR2 X2, D3DXVECTOR2 Y1, D3DXVECTOR2 Y2);
//线-线碰撞检测，返回交叉点
bool LineLineCollision(D3DXVECTOR2 X1, D3DXVECTOR2 X2, D3DXVECTOR2 Y1, D3DXVECTOR2 Y2, D3DXVECTOR2* inter);

//线-矩阵碰撞检测
bool LineRectCollision(D3DXVECTOR2 p1, D3DXVECTOR2 p2, RECT rect);
//线-矩阵碰撞检测，返回第一个交叉点
bool LineRectCollision(D3DXVECTOR2 p1, D3DXVECTOR2 p2, RECT rect, D3DXVECTOR2* pInter1);
//线-矩阵碰撞检测，返回两个交叉点
bool LineRectCollision(D3DXVECTOR2 p1, D3DXVECTOR2 p2, RECT rect, D3DXVECTOR2* pInter1, D3DXVECTOR2* pInter2);

//获取第一个点对应第二个点，相较于X轴的旋转角度。（弧度）
double getRadiansBytwoPoints(float x1, float y1, float x2, float y2);
double getRadiansBytwoPoints(D3DXVECTOR2 p1, D3DXVECTOR2 p2);


//获取物体对应鼠标的旋转位置（弧度）
double GetMouseAngle();