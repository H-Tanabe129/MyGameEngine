//#pragma once
//#include "Direct3D.h"
//#include "Texture.h"
//#include <DirectXMath.h>
//#include <vector>
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
//protected:
//	int vertexNum_;  //頂点数
//	std::vector<VERTEX> vertices_;  //頂点情報
//	int indexNum_;//インデックス数
//	std::vector<int> index_;//インデックス情報
// 
// 
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
//
//private:
//	virtual void InitVertexData();
//	HRESULT CreateVertexBuffer();
//	virtual void InitIndexData();
//	HRESULT CreateIndexBuffer();
//	HRESULT CreateConstantBuffer();
//	HRESULT LoadTexture();
//};
//
