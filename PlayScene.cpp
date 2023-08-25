#include "PlayScene.h"
#include "Engine/Fbx.h"
#include "Player.h"
#include "Enemy.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
  : GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	//Player* pPlayer;
	//pPlayer = new Player(this);  // �v���C���[�̐e�͎���(PlayScene)
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);  // PlayScene�̎q�Ƃ��ăv���C���[��o�^
	Instantiate<Player>(this);	
	Instantiate<Enemy>(this);
}

//�X�V
void PlayScene::Update()
{
	this->transform_.rotate_.y += 1;
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}