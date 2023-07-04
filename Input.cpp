#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	//�L�[�{�[�h
	LPDIRECTINPUTDEVICE8 pKeyDevice;  //�f�o�C�X�I�u�W�F�N�g
	BYTE keyState[256] = { 0 };       //���݂̊e�L�[�̏��
    BYTE prevKeyState[256];    //�O�t���[���ł̊e�L�[�̏��

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);  //�������x��
	}

	void Update()
	{//1�t���[���Ɉ��
		memcpy(prevKeyState, keyState, sizeof(BYTE)*256);

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
        //���͉����ĂāA�O��͉����ĂȂ�
        if (IsKey(keyCode) && !prevKeyState[keyCode] & 0x80)
        {
            return true;
        }
        return false;
    }

    bool IsKeyUp(int keyCode)
    {
		if (!IsKey(keyCode) && prevKeyState[keyCode] & 0x80)
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

