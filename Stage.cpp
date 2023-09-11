#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Direct3D.h"
#include "resource.h"


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
    if (Input::IsMouseButtonDown(0))
    {
        //�r���[�|�[�g�s��
        float w = (float)Direct3D::scrWidth / 2.0f;
        float h = (float)Direct3D::scrHeight / 2.0f;
        XMMATRIX vp = {
            w, 0, 0, 0,
            0,-h, 0, 0,
            0, 0, 1, 0,
            w, h, 0, 1
        };

        //�r���[�|�[�g
        XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
        //�v���W�F�N�V�����ϊ�
        XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
        //�r���[�ϊ�
        XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

        //�}�E�X�ʒu�i��O�j
        XMFLOAT3 mousePosFront = Input::GetMousePosition();
        mousePosFront.z = 0.0f;

        //�}�E�X�ʒu�i���j
        XMFLOAT3 mousePosBack = Input::GetMousePosition();
        mousePosBack.z = 1.0f;

        //�@�@mousePosFront���x�N�g���ɕϊ�
        XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
        //�A�@�@��invVP, invPrj, invView��������
        vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
        //�B�@mousePosBack���x�N�g���ɕϊ�
        XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
        //�C�@�B��invVP, invPrj, invView��������
        vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);

        /*int bufX = -1, bufZ;
        float minDistance = 9999999;*/

        for (int x = 0; x < 15; x++) {
            for (int z = 0; z < 15; z++) {
                for (int y = 0; y < table_[x][z].height + 1; y++) {
                    //�D�@�A����C�Ɍ������ă��C������(�Ƃ肠�������f���ԍ���hModel_[0])
                    RayCastData data;
                    XMStoreFloat4(&data.start, vMouseFront);
                    XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);

                    Transform trans;
                    transform_.position_.x = x;
                    transform_.position_.y = y;
                    transform_.position_.z = z;
                    Model::SetTransform(hModel_[0], trans);
                    Model::RayCast(hModel_[0], data);

                    //�E���C������������u���[�N�|�C���g�Ŏ~�߂�
                    if (data.hit)
                    {
                        table_[x][z].height++;
                        break;
                    }
                }
            }
        }
    }
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

//�U���̃_�C�A���O�v���V�[�W��
BOOL  Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        //�_�C�A���O�ł���
    case WM_INITDIALOG:
        //���W�I�{�^���̏����l
        SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

        //�R���{�{�b�N�X�̏����l
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"�f�t�H���g");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"�����K");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"����");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"���n");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"��");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);



        return TRUE;

    }
    return FALSE;
}