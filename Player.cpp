#include "Player.h"
#include "Engine/Fbx.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), pFbx(nullptr)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/ODEN.fbx");
	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;
}

//更新
void Player::Update()
{
}

//描画
void Player::Draw()
{
	pFbx->Draw(transform_);
}

//開放
void Player::Release()
{
	pFbx->Release();
	delete pFbx;
}