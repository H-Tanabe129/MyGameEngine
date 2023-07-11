#pragma once
#include "Engine/GameObject.h"

class Fbx;  //前方宣言

class Oden :
	public GameObject
{
	Fbx* pFbx;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Oden(GameObject* parent);
	~Oden();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
