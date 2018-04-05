#include "DirectX.h"

LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backbuffer = NULL;

LPD3DXSPRITE spriteOBJ = NULL;
LPD3DXLINE Line = NULL;
LPDIRECTSOUND8 dsound = NULL;

LPDIRECTINPUT8 dinput = NULL;
LPDIRECTINPUTDEVICE8 dikeyboard = NULL;
LPDIRECTINPUTDEVICE8 dimouse = NULL;
DIMOUSESTATE Mouse_State;
char keys[256];

LPDIRECTSOUNDBUFFER sound_test = NULL;

bool Direct_Init(HWND window, int width, int height, bool fullscreen)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d)return false;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.Windowed = (!fullscreen);
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;

	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &d3ddev);
	if (!d3ddev)return false;

	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	D3DXCreateSprite(d3ddev, &spriteOBJ);

	D3DXCreateLine(d3ddev, &Line);

	

	DirectSound_Init(window);

	return true;
}

void Direct_ShutDown()
{
	if (spriteOBJ)spriteOBJ->Release();
	if (Line)Line->Release();
	if (d3ddev)d3ddev->Release();
	if (d3d)d3d->Release();
}

bool DirectSound_Init(HWND window)
{
	HRESULT hr;
	DSBUFFERDESC desc;
	WAVEFORMATEX waveFormat;

	hr = DirectSoundCreate8(NULL, &dsound, NULL);
	if (FAILED(hr))return false;

	dsound->SetCooperativeLevel(window, DSSCL_PRIORITY);

	desc.dwBufferBytes = 0;
	desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	desc.dwReserved = 0;
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.guid3DAlgorithm = GUID_NULL;
	desc.lpwfxFormat = NULL;

	dsound->CreateSoundBuffer(&desc, &sound_test, NULL);

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	sound_test->SetFormat(&waveFormat);

	return true;
}

void DirectSound_ShutDown()
{
	if (dsound)delete dsound;
}

bool DirectInput_Init(HWND window)
{
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, NULL);

	dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);
	dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	dikeyboard->SetCooperativeLevel(window, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	dikeyboard->Acquire();

	dinput->CreateDevice(GUID_SysMouse, &dimouse, NULL);
	dimouse->SetDataFormat(&c_dfDIMouse);
	dimouse->SetCooperativeLevel(window, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	dimouse->Acquire();

	d3ddev->ShowCursor(true);

	return true;
}

void DirectInput_Update()
{
	if (!SUCCEEDED(dikeyboard->GetDeviceState(sizeof(keys), &keys)))dikeyboard->Acquire();
	if (!SUCCEEDED(dimouse->GetDeviceState(sizeof(Mouse_State), &Mouse_State)))dimouse->Acquire();
}

void DirectInput_Shutdonw()
{
	if (dikeyboard)
	{
		dikeyboard->Unacquire();
		dikeyboard->Release();
	}
	if (dimouse)
	{
		dimouse->Unacquire();
		dimouse->Acquire();
	}

	if (dinput)dinput->Release();
}
LPD3DXFONT MakeFont(string name, int size)
{
	LPD3DXFONT font = NULL;
	D3DXFONT_DESC desc = {
		size,		//高度
		0,			//宽度
		0,			//重量？！？！
		0,			//miplevels？！？！
		false,		//是否为斜体
		DEFAULT_CHARSET,	//字符集
		OUT_TT_PRECIS,		//输出精度
		CLIP_DEFAULT_PRECIS,	//质量
		DEFAULT_PITCH,		//字体间距等
		L""			//字体名称
	};

	strcpy_s((char*)desc.FaceName, sizeof(name), name.c_str());

	D3DXCreateFontIndirect(d3ddev, &desc, &font);

	return font;
}

LPDIRECT3DTEXTURE9 LoadTextureNoInfo(wstring filename, D3DCOLOR color)
{
	LPDIRECT3DTEXTURE9 texture;

	HRESULT result;
	D3DXIMAGE_INFO info;
	result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
	if (result != D3D_OK)return NULL;

	D3DXCreateTextureFromFileEx(
		d3ddev,
		filename.c_str(),
		info.Width, info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		color,
		&info,
		NULL,
		&texture);

	return texture;
}

LPDIRECT3DTEXTURE9 LoadTextureWithInfo(wstring filename, D3DCOLOR color, D3DXIMAGE_INFO* info)
{
	LPDIRECT3DTEXTURE9 texture;

	HRESULT result;
	result = D3DXGetImageInfoFromFile(filename.c_str(), info);
	if (result != D3D_OK)return NULL;

	D3DXCreateTextureFromFileEx(
		d3ddev,
		filename.c_str(),
		info->Width, info->Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		color,
		info,
		NULL,
		&texture);

	return texture;
}

void SpriteTransformDraw(LPDIRECT3DTEXTURE9 texture, int x, int y, int width, int height, int frame, int columns, float rotation, float scaling, D3DCOLOR color)
{
	//缩放向量
	D3DXVECTOR2 scale(scaling, scaling);

	//绘制坐标
	D3DXVECTOR2 trans(x, y);

	//计算贴图中心
	D3DXVECTOR2 center((width*scaling) / 2, (height*scaling) / 2);

	//变换矩阵
	D3DXMATRIX mat;
	D3DXMATRIX origin;
	D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, &center, rotation, &trans);

	spriteOBJ->GetTransform(&origin);
	spriteOBJ->SetTransform(&mat);

	//计算要绘制的帧的位置
	int fx = (frame % columns) * width;
	int fy = (frame / columns) * height;
	RECT srcRect = { fx, fy, fx + width, fy + height };

	spriteOBJ->Draw(texture, &srcRect, NULL, NULL, color);

	spriteOBJ->SetTransform(&origin);
}
void Sprite_Animate(int & frame, int startframe, int endframe, int & starttime, int delay)
{
	if (GetTickCount() > starttime + delay)
	{
		starttime = GetTickCount();

		frame++;
		if (frame > endframe) frame = startframe;
		if (frame < startframe) frame = endframe;
	}
}
void Sprite_Animate(int & frame, int startframe, int endframe, int direction, int & starttime, int delay)
{
	if (GetTickCount() > starttime + delay)
	{
		starttime = GetTickCount();

		frame += direction;
		if (frame > endframe) frame = startframe;
		if (frame < startframe) frame = endframe;
	}
}
void Sprite_Draw_Frame(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR3* pos, int framenum, int framew, int frameh, int columns)
{
	RECT rect;
	rect.left = (framenum % columns) * framew;
	rect.top = (framenum / columns) * frameh;
	rect.right = rect.left + framew;
	rect.bottom = rect.top + frameh;

	spriteOBJ->Draw(texture, &rect, NULL, pos, D3DCOLOR_XRGB(255, 255, 255));
}