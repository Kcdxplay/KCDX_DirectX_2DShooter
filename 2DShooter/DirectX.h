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

//D3D�����
extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;
extern LPDIRECTSOUND8 dsound;

//D3D�����豸
extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 dikeyboard;
extern LPDIRECTINPUTDEVICE8 dimouse;
extern DIMOUSESTATE Mouse_State;
extern char keys[256];

//D3D����
extern LPDIRECTSOUNDBUFFER sound_test;

//D3D����
extern LPD3DXSPRITE spriteOBJ;

//D3D����ָ��
extern LPD3DXLINE Line;


/*��������*/
//D3D��ʼ���ͽ���
bool Direct_Init(HWND window, int width, int height, bool fullscreen);
void Direct_ShutDown();

//D3D��������
bool DirectSound_Init(HWND window);
void DirectSound_ShutDown();

//�����豸���
bool DirectInput_Init(HWND window);
void DirectInput_Update();
void DirectInput_Shutdonw();

//��Ϸ�������
bool Game_Init(HWND window);
void Game_Run(HWND window);
void Game_End();
void AI_BootUp();
void Key_Check();

//��������
LPD3DXFONT MakeFont(string name, int size);

//�������
LPDIRECT3DTEXTURE9 LoadTextureNoInfo(wstring filename, D3DCOLOR color = NULL);
LPDIRECT3DTEXTURE9 LoadTextureWithInfo(wstring filename, D3DCOLOR color, D3DXIMAGE_INFO* info);

//���ƺ���
void SpriteTransformDraw(LPDIRECT3DTEXTURE9 texture, int x, int y, int width, int height, int frame, int columns,
							float rotation, float scaling, D3DCOLOR color=0xffffffff);
void Sprite_Animate(int &frame, int startframe, int endframe, int &starttime, int delay);
void Sprite_Animate(int &frame, int startframe, int endframe, int direction, int &starttime, int delay);
void Sprite_Draw_Frame(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR3* pos, int framenum, int framew, int frameh, int columns);
