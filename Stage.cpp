#include "Stage.h"
#include "Engine/Model.h"


void Stage::SetBlockType(int _x, int _z, BLOCKTYPE _type)
{
    //�G���[�`�F�b�N �͈͓��̒l���ǂ����m�F�����ق�������
    table_[_x][_z].height = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
    //�G���[�`�F�b�N
    table_[_x][_z].height = _height;
}

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MODEL_NUM; i++){
        hModel_[i] = -1;
    }
    for (int z = 0; z < ZSIZE; z++){
        for (int x = 0; x < XSIZE; x++){
            SetBlockType(x, z, DEFAULT);
        }
    }
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    string modelname[] = {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx",
    };
    string fname_base = "Assets/";
    for (int i = 0; i < MODEL_NUM; i++)
    {
        //���f���f�[�^�̃��[�h
        hModel_[i] = Model::Load(fname_base + modelname[i]);
        assert(hModel_[i] >= 0);
    }

    //table�Ƀu���b�N�̃^�C�v���Z�b�g���Ă�낤�I

    for (int z = 0; z < ZSIZE; z++){
        for (int x = 0; x < XSIZE; x++){
            SetBlockType(x, z, (BLOCKTYPE)(z % 5));
            SetBlockHeight(x, z, x%5);
        }
    }
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    Transform blockTrans;

    for (int x = 0; x < 15; x++){
        for (int z = 0; z < 15; z++){
            for(int y=0;y<table_[x][z].height + 1;y++){
                int type = table_[x][z].type;
                blockTrans.position_.x = x;
                blockTrans.position_.z = z;
                blockTrans.position_.y = y;

                Model::SetTransform(hModel_[type], blockTrans);
                Model::Draw(hModel_[type]);
            }
        }
    }
}

//�J��
void Stage::Release()
{
}