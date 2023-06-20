//�C���N���[�h
#include <Windows.h>
#include"DIrect3D.h"
#include"Sprite.h"
#include"Dice.h"
//#include"Quad.h"
#include"Camera.h"

//�萔�錾
const char* WIN_CLASS_NAME = "SampleGame";  //�E�B���h�E�N���X��
const char* GAME_TITLE = "�T���v���Q�[��";  //�Q�[���^�C�g��
const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Quad* pQuad = new Quad;
//Dice* pDice = new Dice;
//Sprite* pSprite = new Sprite;

//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;          //�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
	wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j
	RegisterClassEx(&wc); //�N���X��o�^

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);  //FALSE�̓��j���[�̗L��
	int winW = winRect.right - winRect.left;     //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;     //�E�B���h�E����

	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //�E�B���h�E�N���X��
		GAME_TITLE,     //�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,       //�\���ʒu���i���܂����j
		CW_USEDEFAULT,       //�\���ʒu��i���܂����j
		winW,        //�E�B���h�E��
		winH,       //�E�B���h�E����
		NULL,                //�e�E�C���h�E�i�Ȃ��j
		NULL,                //���j���[�i�Ȃ��j
		hInstance,           //�C���X�^���X
		NULL                 //�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;
	//Direct3D������
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))
	{
		PostQuitMessage(0);  //�G���[�N������v���O�����I��
	}

	Camera::Initialize();
	
	//test
	//Camera::SetTarget(XMFLOAT3(2, 0, 0));
	//Camera::SetPosition(XMFLOAT3(0, 0, 0));

	//Quad* pQuad = new Quad;
	//pQuad->Initialize();

	Dice* pDice = new Dice;
	pDice->Initialize();

	Sprite* pSprite = new Sprite;
	pSprite->Initialize();

	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ�
		else
		{
			//�Q�[���̏���
			Camera::Update();
			Direct3D::BeginDraw();
			
			//�`�揈��
			static float angle = 0;
			angle += 0.03;
			XMMATRIX matR = XMMatrixRotationY(XMConvertToRadians(angle));  //��]�s��
			//XMMATRIX matR2 = XMMatrixRotationZ(XMConvertToRadians(angle));//
			XMMATRIX matT = XMMatrixTranslation(1, 0, 0);  //�ړ��s��
			XMMATRIX matS = XMMatrixScaling(2, 2, 2);  //�g��s��
			XMMATRIX mat  = matR * matS * matT; //  //RST

			//pQuad->Draw(mat);
			pDice->Draw(mat);

			mat = XMMatrixScaling(512.0f / 800.0f, 256.0f / 600.0f, 1.0f);
			pSprite->Draw(mat);

			Direct3D::EndDraw();
		}
	}
	//SAFE_RELEASE(pQuad);
	SAFE_RELEASE(pDice);
	SAFE_RELEASE(pSprite);
	//SAFE_DELETE(pQuad);
	SAFE_DELETE(pDice);
	SAFE_DELETE(pSprite);
	Direct3D::Release();

	return 0;

}
//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}