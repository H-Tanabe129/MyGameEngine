#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Fbx.h"
#include "resource.h"


void Stage::SetBlockType(int _x, int _z, BLOCKTYPE _type)
{
    //エラーチェック 範囲内の値かどうか確認したほうがいい
    table_[_x][_z].type = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
    //エラーチェック
    table_[_x][_z].height = _height;
}

//コンストラクタ
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

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    string modelname[] = {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx"
    };
    string fname_base = "Assets/";
    for (int i = 0; i < MODEL_NUM; i++)
    {
        //モデルデータのロード
        hModel_[i] = Model::Load(fname_base + modelname[i]);
        assert(hModel_[i] >= 0);
    }

    //tableにブロックのタイプをセットしてやろう！

    for (int z = 0; z < ZSIZE; z++){
        for (int x = 0; x < XSIZE; x++){
            SetBlockType(x, z, (BLOCKTYPE)(0));
            SetBlockHeight(x, z, 0);
        }
    }
}

//更新
void Stage::Update()
{
    if (!Input::IsMouseButtonDown(0))
    {
        return;
    }

    //ビューポート行列
    float w = (float)(Direct3D::scrWidth / 2.0f);
    float h = (float)(Direct3D::scrHeight / 2.0f);
    //Offsetx,y は0
    //minZ =0 maxZ = 1

    XMMATRIX vp = {
        w, 0, 0, 0,
        0,-h, 0, 0,
        0, 0, 1, 0,
        w, h, 0, 1
    };

    //ビューポート
	XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
	//プロジェクション変換
	XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
	//ビュー変換
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

    //マウス位置（手前）
    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    //マウス位置（奥）
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;
                                                                                                                                                          
    //①　mousePosFrontをベクトルに変換
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    //②　①にinvVP, invPrj, invViewをかける
    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
    //③　mousePosBackをベクトルに変換
    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    //④　③にinvVP, invPrj, invViewをかける
    vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);

    for (int x = 0; x < 15; x++) {
        for (int z = 0; z < 15; z++) {
            for (int y = 0; y < table_[x][z].height + 1; y++) {
                //⑤　②から④に向かってレイをうつ(とりあえずモデル番号はhModel_[0])
                RayCastData data;
                XMStoreFloat4(&data.start, vMouseFront);
                XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);

                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;
                Model::SetTransform(hModel_[0], trans);
                Model::RayCast(hModel_[0], data);

                //⑥レイが当たったらブレークポイントで止める
                if (data.hit && 0<=((y - data.start.y) / data.dir.y )<=1 && mode_ == 0)
                {
                    table_[x][z].height++;
                    break;
                }
                if (data.hit && mode_ == 1 && table_[x][z].height != 0)
                {
                    table_[x][z].height--;
                    break;
                }
                if (data.hit && mode_ == 2)
                {
                    table_[x][z].type = select_;
                    break;
                }
            }
        }
    }
}

//描画
void Stage::Draw()
{
    for (int x = 0; x < 15; x++){
        for (int z = 0; z < 15; z++){
            for(int y=0;y<table_[x][z].height + 1;y++){
                int type = table_[x][z].type;
                Transform blockTrans;
                blockTrans.position_.x = x;
                blockTrans.position_.z = z;
                blockTrans.position_.y = y;

                Model::SetTransform(hModel_[type], blockTrans);
                Model::Draw(hModel_[type]);
            }
        }
    }
}

void Stage::Upward()
{
    for (int x = 0; x < 15; x++) {
        for (int z = 0; z < 15; z++) {
            for (int y = 0; y <= table_[x][z].height; y++) {
                // Y座標を+1する
                table_[x][z].height += 1;
            }
        }
    }
}

void Stage::Downward()
{
    //for (int x = 0; x < 15; x++) {
    //    for (int z = 0; z < 15; z++) {
    //        for (int y = 0; y <= table_[x][z].height; y++) {
    //                // Y座標を-1する
    //                table_[x][z].height -= 1;
    //        }
    //    }
    //}
}

void Stage::Reset()
{
    for (int z = 0; z < ZSIZE; z++) {
        for (int x = 0; x < XSIZE; x++) {
            SetBlockType(x, z, (BLOCKTYPE)(0));
            SetBlockHeight(x, z, 0);
        }
    }
}

//開放
void Stage::Release()
{
}

//偽物のダイアログプロシージャ
BOOL  Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        //ダイアログできた
    case WM_INITDIALOG:
        //ラジオボタンの初期値
        SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

        //コンボボックスの初期値
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"デフォルト");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"レンガ");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"草原");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"砂地");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"水");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);

        return TRUE;



    case WM_COMMAND:
            if (HIWORD(wp) == BN_CLICKED)
            {
                //何押したか取得
                int radioButtonId = LOWORD(wp);
                switch (radioButtonId)
                {
                case IDC_RADIO_UP:
                    mode_ = 0;
                    break;
                case IDC_RADIO_DOWN:
                    mode_ = 1;
                    break;
                case IDC_RADIO_CHANGE:
                    mode_ = 2;
                    break;
                case IDC_BUTTON_UP:
                    Upward();
                    break;
                case IDC_BUTTON_DOWN:
                    Downward();
                    break;
                case IDC_BUTTON_RESET:
                    Reset();
                    break;
                }
                return TRUE;
            }

            /*if (HIWORD(lp) == BN_CLICKED)
            {
                int comboBoxId = LOWORD(lp);
                switch (comboBoxId)
                {
                case SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"デフォルト"):
                }
            }*/
    }
    return FALSE;
}

void Stage::Save()
{
    char fileName[MAX_PATH] = "無題.map";  //ファイル名を入れる変数

    //「ファイルを保存」ダイアログの設定
    OPENFILENAME ofn;                         	//名前をつけて保存ダイアログの設定用構造体
    ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
    ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
    ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")        //─┬ファイルの種類
        TEXT("すべてのファイル(*.*)\0*.*\0\0");     //─┘
    ofn.lpstrFile = fileName;               	//ファイル名
    ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
    ofn.Flags = OFN_OVERWRITEPROMPT;   		//フラグ（同名ファイルが存在したら上書き確認）
    ofn.lpstrDefExt = "map";                  	//デフォルト拡張子

    //「ファイルを保存」ダイアログ
    BOOL selFile;
    selFile = GetSaveFileName(&ofn);

    //キャンセルしたら中断
    if (selFile == FALSE) return;


    HANDLE hFile;        //ファイルのハンドル
    hFile = CreateFile(
        fileName,                 //ファイル名
        GENERIC_WRITE,           //アクセスモード（書き込み用）
        0,                      //共有（なし）
        NULL,                   //セキュリティ属性（継承しない）
        CREATE_ALWAYS,          //作成方法
        FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
        NULL);                  //拡張属性（なし）
}

void Stage::Load()
{
  OPENFILENAME ofn;
  char fileName[MAX_PATH] = "";  //ファイル名を入れる変数
  ZeroMemory(&ofn, sizeof(OPENFILENAME));
  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")        //─┬ファイルの種類
                    TEXT("すべてのファイル(*.*)\0*.*\0\0");     //─┘
  ofn.lpstrFile =   fileName;
  ofn.nMaxFile =    MAX_PATH;
  ofn.Flags =       OFN_FILEMUSTEXIST;
GetOpenFileName(&ofn);


  HANDLE hFile;        //ファイルのハンドル
  hFile = CreateFile(
      fileName,                 //ファイル名
      GENERIC_READ,           //アクセスモード（読み込み用）
      0,                      //共有（なし）
      NULL,                   //セキュリティ属性（継承しない）
      OPEN_EXISTING,           //作成方法
      FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
      NULL);                  //拡張属性（なし）

  ////ファイルのサイズを取得
  //DWORD fileSize = GetFileSize(hFile, NULL);

  ////ファイルのサイズ分メモリを確保
  //char* data;
  //data = new char[fileSize];

  //DWORD dwBytes = 0; //読み込み位置

  //HANDLE hFile;        //ファイルのハンドル
  //hFile = ReadFile(
  //    hFile,     //ファイルハンドル
  //    data,      //データを入れる変数
  //    fileSize,  //読み込むサイズ
  //    &dwBytes,  //読み込んだサイズ
  //    NULL);     //オーバーラップド構造体（今回は使わない）
}
