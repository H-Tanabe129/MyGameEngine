#include "Oden.h"
#include "Engine/Fbx.h"

//�R���X�g���N�^
Oden::Oden(GameObject* parent)
	:GameObject(parent, "Oden"), pFbx(nullptr)
{
}

//�f�X�g���N�^
Oden::~Oden()
{
}

//������
void Oden::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/ODEN.fbx");
	this->transform_.scale_.x = 0.3;
	this->transform_.scale_.y = 0.3;
	this->transform_.scale_.z = 0.3;
	this->transform_.position_.x = 2;
}

//�X�V
void Oden::Update()
{
	transform_.rotate_.y++;
	//KillMe();
}

//�`��
void Oden::Draw()
{
	pFbx->Draw(transform_);
}

//�J��
void Oden::Release()
{
	pFbx->Release();
	delete pFbx;
}