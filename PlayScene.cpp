#include "PlayScene.h"
#include "Engine/Fbx.h"
#include "Player.h"
#include "Enemy.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
  : GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	//Player* pPlayer;
	//pPlayer = new Player(this);  // プレイヤーの親は自分(PlayScene)
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);  // PlaySceneの子としてプレイヤーを登録
	Instantiate<Player>(this);	
	Instantiate<Enemy>(this);
}

//更新
void PlayScene::Update()
{
	this->transform_.rotate_.y += 1;
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}