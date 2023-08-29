#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

Controller::Controller(GameObject* parent) :GameObject(parent, "Controller")
{
	transform_.position_.x = 7.0f;
	transform_.position_.z = 7.0f;

	transform_.rotate_.x = 45.0f;
}

Controller::~Controller()
{
}

void Controller::Initialize()
{
}

void Controller::Update()
{
	//回転
	if (Input::IsKey(DIK_RIGHT))
		transform_.rotate_.y -= 1;
	if (Input::IsKey(DIK_LEFT))
		transform_.rotate_.y += 1;
	if (Input::IsKey(DIK_UP))
	{
		transform_.rotate_.x += 1;
		if (transform_.rotate_.x >= 90)
			transform_.rotate_.x = 89;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		transform_.rotate_.x -= 1;
		if (transform_.rotate_.x < 0)
			transform_.rotate_.x = 0;
	}

	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));		//transform_.rotate_.y度回転させる行列を作成
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));		//transform_.rotate_.x度回転させる行列を作成
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);								//現在地をベクトル型に変換

	//前後移動
	XMVECTOR frontMove = XMVectorSet( 0, 0, 0.1f, 0 );			//奥向きのXMVECTOR構造体を用意する //1フレームの移動ベクトル
	frontMove = XMVector3TransformCoord(frontMove, mRotY);		//移動ベクトルを変形（本体と同じ向きに回転）させる
	if (Input::IsKey(DIK_W))
		vPos += frontMove;
	if (Input::IsKey(DIK_S))
		vPos -= frontMove;

	//現在地をベクトルからいつものtransform_.position_に戻す
	XMStoreFloat3(&transform_.position_, vPos);


	//左右移動
	XMVECTOR rightMove = XMVectorSet(0.1f, 0, 0, 0);			//奥向きのXMVECTOR構造体を用意する //1フレームの移動ベクトル
	rightMove = XMVector3TransformCoord(rightMove, mRotY);		//移動ベクトルを変形（本体と同じ向きに回転）させる

	if (Input::IsKey(DIK_D))
		vPos += rightMove;
	if (Input::IsKey(DIK_A))
		vPos -= rightMove;

	//現在地をベクトルからいつものtransform_.position_に戻す
	XMStoreFloat3(&transform_.position_, vPos);


	//カメラ
	XMVECTOR vCam = XMVectorSet(0, 0, -10, 0);				//自撮り棒
	vCam = XMVector3TransformCoord(vCam, mRotX * mRotY);	//自撮り棒回転
	Camera::SetPosition(vPos + vCam);						//カメラの位置は自撮り棒の先端
	Camera::SetTarget(transform_.position_);				//カメラの見る位置はこのオブジェクトの位置
}

void Controller::Draw()
{
}

void Controller::Release()
{
}
