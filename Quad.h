//#pragma once
//#include "Direct3D.h"
//#include "Texture.h"
//#include <DirectXMath.h>
//
//using namespace DirectX;
//
////コンスタントバッファー
//struct CONSTANT_BUFFER
//{
//	XMMATRIX	matWVP;
//	XMMATRIX	matW;
//};
//
//struct VERTEX
//{
//	XMVECTOR position;
//	XMVECTOR uv;
//	XMVECTOR normal;
//};
//
//class Quad
//{
//	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
//	ID3D11Buffer *pIndexBuffer_;	//インデックスバッファ
//	ID3D11Buffer *pConstantBuffer_;	//コンスタントバッファ
//	
//	Texture*	pTexture_;
//public:
//	Quad();
//	~Quad();
//	HRESULT Initialize();
//	void Draw(XMMATRIX &worldMatrix);
//	void Release();
//};
//
