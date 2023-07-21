#include "Oden.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
#include "Engine/SphereCollider.h"

//コンストラクタ
Oden::Oden(GameObject* parent)
	:GameObject(parent, "Oden"), pFbx(nullptr), hModel_(-1)
{
}

//デストラクタ
Oden::~Oden()
{
}

//初期化
void Oden::Initialize()
{
	hModel_ = Model::Load("Assets/ODEN.fbx");
	assert(hModel_ >= 0);

	transform_.scale_.x = 0.27f;
	transform_.scale_.y = 0.27f;
	transform_.scale_.z = 0.27f;
	//this->transform_.position_.x = 2.0f;
	//this->transform_.position_.y = 1.5f;
	SphereCollider* col = new SphereCollider(1.0f);
	AddCollider(col);
}

//更新
void Oden::Update()
{
	transform_.rotate_.y++;
	transform_.position_.z += 0.5f;
	if (transform_.position_.z > 50)
	{
		KillMe();
	}
}

//描画
void Oden::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Oden::Release()
{
}