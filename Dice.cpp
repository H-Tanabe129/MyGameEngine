#include "Dice.h"
#include "Camera.h"

Dice::Dice()
	: pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr)
{
}

Dice::~Dice()
{
	Release();  //SAFE_RELEASE�ɏ���������
}

HRESULT Dice::Initialize()
{
	HRESULT hr;
	// ���_���
	VERTEX vertices[/*4*/] =
	{
		//����
		//XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f),	// �l�p�`�̒��_�i��j
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����j0
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j1
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�����j3	
		//�E
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����j4
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j5	
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j6	
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�����j7	
		////��
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����j8
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j9
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j10
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�����j11
		//��
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����j12
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j13
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j14
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�����j15
		//��
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����j16
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j17
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j18
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�����j19
		//��
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�����j20
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j21	
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j22
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����j23

	};

	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;

	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "���_�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}


	//�C���f�b�N�X���
	int index[] = { 0,1,2, 0,2,3, 4,5,6, 4,6,7, 8,9,10, 8,10,11, 
		12,13,14, 12,14,15, 16,17,18, 16,18,19, 20,21,22, 20,22,23, };

	// �C���f�b�N�X�o�b�t�@�𐶐�����
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}


	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}

	pTexture_ = new Texture();
	pTexture_->Load("Assets\\Dice.png");

	return S_OK;
}

void Dice::Draw(XMMATRIX& worldMatrix) //& �Q�ƂɂȂ�
{
	//�R���X�^���g�o�b�t�@�ɓn�����
	//XMVECTOR position = { 0, 3, -10, 0 };	//�J�����̈ʒu
	//XMVECTOR target = { 0, 0, 0, 0 };	//�J�����̏œ_
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//�r���[�s��
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4/*�c�̉�p�A����p��׼ޱ݂Ŏw�肵������*/, 800.0f / 600.0f, 0.1f, 100.0f);//�ˉe�s��

	D3D11_MAPPED_SUBRESOURCE pdata;
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());

	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ


	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);


	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);


	//�R���X�^���g�o�b�t�@
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

	Direct3D::pContext_->DrawIndexed(36, 0, 0);
}

void Dice::Release()
{
	pTexture_->Release();
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}