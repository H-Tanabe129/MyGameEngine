#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MD.lib")  // MT��MD
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Texture; //�O���錾 �|�C���^�ϐ������Ȃ�

class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture*	pTexture;
	};

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	struct VERTEX
	{
		XMVECTOR position;
	};

	ID3D11Buffer *pVertexBuffer_;
	ID3D11Buffer *pIndexBuffer_;
	ID3D11Buffer *pConstantBuffer_;
	MATERIAL* pMaterialList_;

	//Texture* pTexture_;

public:
	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();

private:
	void InitMaterial(fbxsdk::FbxNode* pNode);
	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
};

