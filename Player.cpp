#include "Player.h"
#include "Oden.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), pFbx(nullptr), hModel_(-1)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
	hModel_ = Model::Load("Assets/ODEN.fbx");
	assert(hModel_ >= 0);

	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;

	//Instantiate<Oden>(this);
	//GameObject* pCO2 = Instantiate<Oden>(this);
	//pCO2->SetPosition(-2.0f, 1.5f, 0.0f);
}

//�X�V
void Player::Update()
{
	transform_.rotate_.y++;

	//if (transform_.rotate_.y > 600)
	//{
	//	KillMe();
	//}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += 0.2f;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= 0.2f;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		GameObject* pBullet = Instantiate<Oden>(pParent_);
		pBullet->SetPosition(transform_.position_);
	}

}

//�`��
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
	//pFbx->Release();
	//delete pFbx;
}