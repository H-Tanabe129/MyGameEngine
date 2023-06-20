#include "Dice.h"

//���_���̏���
void Dice::InitVertexData()
{
	// ���_���
	vertices_ =
	{
		//����
		//XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f),	// �l�p�`�̒��_�i��j
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},	// �l�p�`�̒��_�i����j0
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j1
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},	// �l�p�`�̒��_�i�����j3	
		//�E
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����j4
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j5	
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j6	
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�����j7	
		////��
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},	// �l�p�`�̒��_�i����j8
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j9
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j10
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},	// �l�p�`�̒��_�i�����j11
		//��
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����j12
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j13
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j14
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�����j15
		//��
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����j16
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j17
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j18
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�����j19
		//��
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�����j20
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j21	
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j22
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����j23

	};

	//���_�̐�
	vertexNum_ = vertices_.size();
}

//�C���f�b�N�X��������
void Dice::InitIndexData()
{
	index_ = { 0,1,2, 0,2,3, 4,5,6, 4,6,7, 8,9,10, 8,10,11,
		   12,13,14, 12,14,15, 16,17,18, 16,18,19, 20,21,22, 20,22,23, };

	//�C���f�b�N�X��
	indexNum_ = index_.size();
}