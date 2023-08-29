#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

Controller::Controller(GameObject* parent) :GameObject(parent, "Controller")
{
	transform_.position_.x = 7.0f;
	transform_.position_.z = 7.0f;

	transform_.rotate_.x = 45.0f;
}

Controller::~Controller()
{
}

void Controller::Initialize()
{
}

void Controller::Update()
{
	//��]
	if (Input::IsKey(DIK_RIGHT))
		transform_.rotate_.y -= 1;
	if (Input::IsKey(DIK_LEFT))
		transform_.rotate_.y += 1;
	if (Input::IsKey(DIK_UP))
	{
		transform_.rotate_.x += 1;
		if (transform_.rotate_.x >= 90)
			transform_.rotate_.x = 89;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		transform_.rotate_.x -= 1;
		if (transform_.rotate_.x < 0)
			transform_.rotate_.x = 0;
	}

	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));		//transform_.rotate_.y�x��]������s����쐬
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));		//transform_.rotate_.x�x��]������s����쐬
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);								//���ݒn���x�N�g���^�ɕϊ�

	//�O��ړ�
	XMVECTOR frontMove = XMVectorSet( 0, 0, 0.1f, 0 );			//��������XMVECTOR�\���̂�p�ӂ��� //1�t���[���̈ړ��x�N�g��
	frontMove = XMVector3TransformCoord(frontMove, mRotY);		//�ړ��x�N�g����ό`�i�{�̂Ɠ��������ɉ�]�j������
	if (Input::IsKey(DIK_W))
		vPos += frontMove;
	if (Input::IsKey(DIK_S))
		vPos -= frontMove;

	//���ݒn���x�N�g�����炢����transform_.position_�ɖ߂�
	XMStoreFloat3(&transform_.position_, vPos);


	//���E�ړ�
	XMVECTOR rightMove = XMVectorSet(0.1f, 0, 0, 0);			//��������XMVECTOR�\���̂�p�ӂ��� //1�t���[���̈ړ��x�N�g��
	rightMove = XMVector3TransformCoord(rightMove, mRotY);		//�ړ��x�N�g����ό`�i�{�̂Ɠ��������ɉ�]�j������

	if (Input::IsKey(DIK_D))
		vPos += rightMove;
	if (Input::IsKey(DIK_A))
		vPos -= rightMove;

	//���ݒn���x�N�g�����炢����transform_.position_�ɖ߂�
	XMStoreFloat3(&transform_.position_, vPos);


	//�J����
	XMVECTOR vCam = XMVectorSet(0, 0, -10, 0);				//���B��_
	vCam = XMVector3TransformCoord(vCam, mRotX * mRotY);	//���B��_��]
	Camera::SetPosition(vPos + vCam);						//�J�����̈ʒu�͎��B��_�̐�[
	Camera::SetTarget(transform_.position_);				//�J�����̌���ʒu�͂��̃I�u�W�F�N�g�̈ʒu
}

void Controller::Draw()
{
}

void Controller::Release()
{
}
