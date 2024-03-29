#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	//キーボード
	LPDIRECTINPUTDEVICE8 pKeyDevice;  //デバイスオブジェクト
	BYTE keyState[256] = { 0 };       //現在の各キーの状態
    BYTE prevKeyState[256];    //前フレームでの各キーの状態

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);  //強調レベル
	}

	void Update()
	{//1フレームに一回
		memcpy(prevKeyState, keyState, sizeof(prevKeyState));

		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)
		{
			return true;
		}
			return false;
	}

    bool IsKeyDown(int keyCode)
    {
        //今は押してて、前回は押してない
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80))
        {
            return true;
        }
        return false;
    }

    bool IsKeyUp(int keyCode)
    {
		//今は押してなくて、前回は押してる
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
    }
	
	/*XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
	}*/

	void Release()
	{
		SAFE_RELEASE(pDInput);
	}
}

