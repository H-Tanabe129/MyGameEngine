#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
#include "Engine/SphereCollider.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
    pFbx = new Fbx;
    pFbx->Load("Assets/ODEN.fbx");
    transform_.position_.z = 20.0f;

    SphereCollider* collision = new SphereCollider(10.0f);
    AddCollider(collision);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
    pFbx->Draw(transform_);
}

void Enemy::Release()
{
}
