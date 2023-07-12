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
	//ˆÚ“®s—ñì¬
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	//‰ñ“]s—ñì¬
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x)); // XŽ²
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y)); // YŽ²
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z)); // ZŽ²
	matRotate_ = rotateZ * rotateX * rotateY;		//‡‘Ì

	//Šg‘ås—ñì¬
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
	if (pParent_ /* != nullptr */)  //•ÛØ‚³‚ê‚Ä‚é
	{
		//e‚ª‚ ‚Á‚½‚ç
		return matTranslate_ * matRotate_ * matScale_ * pParent_->GetWorldMatrix();
	}else
		return matScale_ * matRotate_ * matTranslate_;
}

XMMATRIX Transform::GetNormalMatrix()
{
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}
