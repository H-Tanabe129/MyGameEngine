#include "Transform.h"

Transform::Transform() :
    matTranslate_(XMMatrixIdentity()),
    matRotate_(XMMatrixIdentity()),
    matScale_(XMMatrixIdentity()),
    position_(XMFLOAT3(0, 0, 0)),
    rotate_(XMFLOAT3(0, 0, 0)),
    scale_(XMFLOAT3(1, 1, 1))
{
}

Transform::~Transform()
{
}

void Transform::Calclation()
{
	//移動行列作成
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	//回転行列作成
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x)); // X軸
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y)); // Y軸
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z)); // Z軸
	matRotate_ = rotateZ * rotateX * rotateY;		//合体

	//拡大行列作成
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
	if (pParent_ /* != nullptr */)  //保証されてる
	{
		//親があったら
		return matTranslate_ * matRotate_ * matScale_ * pParent_->GetWorldMatrix();
	}else
		return matScale_ * matRotate_ * matTranslate_;
}

XMMATRIX Transform::GetNormalMatrix()
{
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}
