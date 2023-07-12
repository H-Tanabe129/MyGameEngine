#include "Player.h"
#include "Oden.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), pFbx(nullptr)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/ODEN.fbx");
	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;

	Instantiate<Oden>(this);
	GameObject* pCO2 = Instantiate<Oden>(this);
	pCO2->transform_.position_.x = 
}

//�X�V
void Player::Update()
{
	transform_.rotate_.y++;
	//KillMe();

	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += 0.2f;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= 0.2f;
	}

}

//�`��
void Player::Draw()
{
	pFbx->Draw(transform_);
}

//�J��
void Player::Release()
{
	pFbx->Release();
	delete pFbx;
}