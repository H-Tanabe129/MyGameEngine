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
	//���f���̃|�C���^���Ԃ�����ł����x�N�^
	std::vector<ModelData*>modelList;
}



int Model::Load(std::string fileName)
{
	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	//�t�@�C���l�[����������������ǂ܂�
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

	//�t�@�C�����̃��f����ǂݍ���ŁA�������f�����̂��̂��������炻�̃��f���ԍ��i�z��̃C���f�b�N�X-1�j��Ԃ��֐�
	//�������O�̃��f�����Ȃ�������A���f����ǂݍ���ŁA�x�N�^�ɒǉ�
}

void Model::SetTransform(int hModel, Transform transform)
{
	//���f���ԍ���modelList�̃C���f�b�N�X
	modelList[hModel]->transform_ = transform;
}

void Model::Draw(int hModel) {
	//���f���ԍ���modelList�̃C���f�b�N�X
	modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isReferred = false;  //�Q�Ƃ��Ă邩�ǂ���
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