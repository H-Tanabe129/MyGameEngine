#include "GameObject.h"
#include "SphereCollider.h"

GameObject::GameObject() :pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name): pParent_(parent), IsDead_(false), objectName_(name), pCollider_(nullptr)
{
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
}

void GameObject::UpdateSub()
{
	Update();

	RoundRobin(GetRootJob());
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->UpdateSub();
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->IsDead_ == true)
		{
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void GameObject::ReleaseSub()
{
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();//*itrのリリースを呼ぶ
		SAFE_DELETE(*itr);//*itr自体を消す
	}
	Release();
}

void GameObject::KillMe()
{
	IsDead_ = true;
}

void GameObject::SetPosition(XMFLOAT3(position))
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	SetPosition(XMFLOAT3(x, y, z));
}

GameObject* GameObject::FindChildObject(string _objName)
{
	if(_objName == this->objectName_)
	{
		return (this);  //自分が_objectNameのオブジェクトだった！
	}
	else
	{
		//for (auto itr = childList_.begin(); itr!=childList_.end(); itr++)
		for(auto itr: childList_)
		{
			GameObject* obj = (itr)->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}
}

/// <summary>
/// 再起呼び出しでRootJobを探してそのアドレスを返す関数
/// </summary>
/// <returns>RootJobのアドレス(GameObject * 型）</returns>
GameObject* GameObject::GetRootJob()
{
	if(pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName)
{
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(objectName_);
	return (result);
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	if (pTarget == this || pTarget->pCollider_ == nullptr)
		return;  //自分自身、またはターゲットにコライダーがアタッチされていない

	/*XMVECTOR v{ transform_.position_.x - pTarget->transform_.position_.x,
	transform_.position_.y - pTarget->transform_.position_.y,
	transform_.position_.z - pTarget->transform_.position_.z, 0};
	XMVECTOR dist = XMVector3Dot(v, v);*/

	float dist = (transform_.position_.x - pTarget->transform_.position_.x) * (transform_.position_.x - pTarget->transform_.position_.x) +
		(transform_.position_.y - pTarget->transform_.position_.y) * (transform_.position_.y - pTarget->transform_.position_.y) +
		(transform_.position_.z - pTarget->transform_.position_.z) * (transform_.position_.z - pTarget->transform_.position_.z);
	float rDist = (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius()) * (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius());

	//自分とターゲットの距離　<=　R1+R2なら
	//もし自分のコライダーとターゲットがぶつかってたらonCollisionを呼び出す
	if (dist <= rDist)
	{
		//onCollistion(pTarget)
		double p = 0;
	}
}

void GameObject::RoundRobin(GameObject* pTarget)
{
	if (pCollider_ == nullptr)
		return;
	if (pTarget->pCollider_ != nullptr)  //自分とターゲット
		Collision(pTarget);
	//自分の子供全部とターゲット
	for (auto&& itr : childList_)
		RoundRobin(itr);
}

