//インクルード
#include <Windows.h>
#include"DIrect3D.h"
#include"Sprite.h"
#include"Dice.h"
//#include"Quad.h"
#include"Camera.h"

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const char* GAME_TITLE = "サンプルゲーム";  //ゲームタイトル
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Quad* pQuad = new Quad;
//Dice* pDice = new Dice;
//Sprite* pSprite = new Sprite;

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;          //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	RegisterClassEx(&wc); //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);  //FALSEはメニューの有無
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		GAME_TITLE,     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,        //ウィンドウ幅
		winH,       //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;
	//Direct3D初期化
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))
	{
		PostQuitMessage(0);  //エラー起きたらプログラム終了
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

	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			//ゲームの処理
			Camera::Update();
			Direct3D::BeginDraw();
			
			//描画処理
			static float angle = 0;
			angle += 0.03;
			XMMATRIX matR = XMMatrixRotationY(XMConvertToRadians(angle));  //回転行列
			//XMMATRIX matR2 = XMMatrixRotationZ(XMConvertToRadians(angle));//
			XMMATRIX matT = XMMatrixTranslation(1, 0, 0);  //移動行列
			XMMATRIX matS = XMMatrixScaling(2, 2, 2);  //拡大行列
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
//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}