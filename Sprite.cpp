#include "Sprite.h"

Sprite::Sprite()
	: pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr),pTexture_(nullptr)
{
}

Sprite::~Sprite()
{
	Release();  //SAFE_RELEASE‚É‘‚«Š·‚¦‚é
}

HRESULT Sprite::Initialize()
{
}

void Sprite::Draw(XMMATRIX& worldMatrix)
{
	Direct3D::SetShader(SHADER_2D);

	//
	PassDaraToCB(worldMatrix);

	//
	SetBufferToPipeline();

	//
	Direct3D::pContext_->DrawIndexed(indexNum_, 0, 0);
}

void Sprite::Release()
{
		SAFE_DELETE(pTexture_);
	
		SAFE_RELEASE(pConstantBuffer_);
		SAFE_RELEASE(pIndexBuffer_);
		SAFE_RELEASE(pVertexBuffer_);
}

void Sprite::InitVertexData()
{
}

HRESULT Sprite::CreateVertexBuffer()
{
	return E_NOTIMPL;
}

void Sprite::InitIndexData()
{
}

HRESULT Sprite::CreateIndexBuffer()
{
	return E_NOTIMPL;
}

HRESULT Sprite::CreateConstantBuffer()
{
	return E_NOTIMPL;
}

HRESULT Sprite::LoadTexture()
{
	return E_NOTIMPL;
}

void Sprite::PassDaraToCB(DirectX::XMMATRIX& worldMatrix)
{
}

void Sprite::SetBufferToPipeline()
{
}
