#pragma once
#include "Engine/GameObject.h"

class Fbx;  //�O���錾

class Player :
    public GameObject
{
	Fbx* pFbx;
	int hModel_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);
	~Player();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

