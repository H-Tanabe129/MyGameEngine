#include "Model.h"
#include<vector>
#include "DIrect3D.h"

namespace Model{
	struct ModelData
	{
		Fbx* pfbx_;
		Transform transform_;
		std::string filename_;
	};
	//モデルのポインタをぶち込んでおくベクタ
	std::vector<ModelData*>modelList;
}



int Model::Load(std::string fileName)
{
	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	//ファイルネームが同じだったら読まん
	for (auto& e : modelList)
	{
		if (e->filename_ == fileName){
			pData->pfbx_ = e->pfbx_;
			break;
		}
	}
	
	if (pData->pfbx_ == nullptr)
	{
		pData->pfbx_ = new Fbx;
		pData->pfbx_->Load(fileName);
	}

	modelList.push_back(pData);
	return (modelList.size() - 1);

	//ファイル名のモデルを読み込んで、同じモデル名のものがあったらそのモデル番号（配列のインデックス-1）を返す関数
	//同じ名前のモデルがなかったら、モデルを読み込んで、ベクタに追加
}

void Model::SetTransform(int hModel, Transform transform)
{
	//モデル番号はmodelListのインデックス
	modelList[hModel]->transform_ = transform;
}

void Model::Draw(int hModel) {
	//モデル番号はmodelListのインデックス
	modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isReferred = false;  //参照してるかどうか
	for (int i = 0; i < modelList.size(); i++)
	{
		for (int j = i + 1; j < modelList.size(); j++)
		{
			if (modelList[i]->pfbx_ == modelList[j]->pfbx_)
			{
				isReferred = true;
				break;
			}
		}
		if (isReferred == false)
		{
			SAFE_DELETE(modelList[i]->pfbx_);
		}
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear();
}