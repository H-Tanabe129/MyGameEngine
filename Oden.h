#pragma once
#include "Engine/GameObject.h"

class Fbx;  //�O���錾

class Oden :
	public GameObject
{
	Fbx* pFbx;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Oden(GameObject* parent);
	~Oden();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
