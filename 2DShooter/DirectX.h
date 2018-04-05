	#pragma once

#include <Windows.h>
#include <iostream>
#include <time.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <XInput.h>
#include <dsound.h>
#include <stdio.h>

#include "Tools.h"

using namespace std;

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")
#pragma comment(lib,"dsound.lib")

extern const wstring Tittle;
extern const int SCREENW;
extern const int SCREENH;
extern bool gameover;

//D3D对象等
extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;
extern LPDIRECTSOUND8 dsound;

//D3D输入设备
extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 dikeyboard;
extern LPDIRECTINPUTDEVICE8 dimouse;
extern DIMOUSESTATE Mouse_State;
extern char keys[256];

//D3D声音
extern LPDIRECTSOUNDBUFFER sound_test;

//D3D精灵
extern LPD3DXSPRITE spriteOBJ;

//D3D其它指针
extern LPD3DXLINE Line;


/*函数部分*/
//D3D初始化和结束
bool Direct_Init(HWND window, int width, int height, bool fullscreen);
void Direct_ShutDown();

//D3D声音函数
bool DirectSound_Init(HWND window);
void DirectSound_ShutDown();

//输入设备相关
bool DirectInput_Init(HWND window);
void DirectInput_Update();
void DirectInput_Shutdonw();

//游戏流程相关
bool Game_Init(HWND window);
void Game_Run(HWND window);
void Game_End();
void AI_BootUp();
void Key_Check();

//创建字体
LPD3DXFONT MakeFont(string name, int size);

//加载相关
LPDIRECT3DTEXTURE9 LoadTextureNoInfo(wstring filename, D3DCOLOR color = NULL);
LPDIRECT3DTEXTURE9 LoadTextureWithInfo(wstring filename, D3DCOLOR color, D3DXIMAGE_INFO* info);

//绘制函数
void SpriteTransformDraw(LPDIRECT3DTEXTURE9 texture, int x, int y, int width, int height, int frame, int columns,
							float rotation, float scaling, D3DCOLOR color=0xffffffff);
void Sprite_Animate(int &frame, int startframe, int endframe, int &starttime, int delay);
void Sprite_Animate(int &frame, int startframe, int endframe, int direction, int &starttime, int delay);
void Sprite_Draw_Frame(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR3* pos, int framenum, int framew, int frameh, int columns);
