#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include "Texture.h"

#pragma comment(lib, "LibFbxSDK-MD.lib")  // MTÅ®MD
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	struct VERTEX
	{
		XMVECTOR position;
	};

	int vertexCount_;	//í∏ì_êî
	int polygonCount_;	//É|ÉäÉSÉìêî

	ID3D11Buffer *pVertexBuffer_;
	ID3D11Buffer *pIndexBuffer_;
	ID3D11Buffer *pConstantBuffer_;

	Texture* pTexture_;
public:

	Fbx();
	HRESULT Load(std::string fileName);
	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	HRESULT IntConstantBuffer();
	void    Draw(Transform& transform);
	void    Release();
	void PassDataToCB(Transform transform);
	void SetBufferToPipeline();
};

