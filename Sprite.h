#pragma once
#include "Direct3D.h"
#include "Texture.h"
#include <DirectXMath.h>
#include <vector>

using namespace DirectX;
//#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

class Sprite
{
	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;  //ワールド行列
	};
	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};
	protected:
	UINT64 vertexNum_;  //頂点数
	std::vector<VERTEX> vertices_;  //頂点情報
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ

	UINT64 indexNum_;//インデックス数
	std::vector<int> index_;//インデックス情報
	
	ID3D11Buffer *pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer *pConstantBuffer_;	//コンスタントバッファ
	
	Texture*	pTexture_;
	public:
	Sprite();
	~Sprite();

	//初期化（ポリゴンを表示するための各種情報を準備）
	//戻り値：成功/失敗
	HRESULT Initialize();
	
	//描画
	//引数：worldMatrix ワールド行列
	void Draw(XMMATRIX &worldMatrix);
	//解放
	void Release();
private:
	//------------Initializeから呼ばれる関数-----------------
	virtual void InitVertexData();  //頂点情報の作成
	HRESULT CreateVertexBuffer(); //頂点バッファを作成

	virtual void InitIndexData();  //インデックス情報を準備
	HRESULT CreateIndexBuffer();  //インデックスバッファを作成

	HRESULT CreateConstantBuffer();  //コンスタントバッファ作成
	HRESULT LoadTexture();  //テクスチャをロード
	
	//------------Draw関数から呼ばれる関数-----------------
	void PassDaraToCB(DirectX::XMMATRIX& worldMatrix);  //コンスタントバッファ作成
	void SetBufferToPipeline();  //各バッファをパイプライン
};

