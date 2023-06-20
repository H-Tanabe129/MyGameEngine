#include "Dice.h"

//頂点情報の準備
void Dice::InitVertexData()
{
	// 頂点情報
	vertices_ =
	{
		//正面
		//XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f),	// 四角形の頂点（上）
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},	// 四角形の頂点（左上）0
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},	// 四角形の頂点（右上）1
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},	// 四角形の頂点（右下）2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},	// 四角形の頂点（左下）3	
		//右
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// 四角形の頂点（左上）4
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// 四角形の頂点（右上）5	
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// 四角形の頂点（右下）6	
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// 四角形の頂点（左下）7	
		////奥
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},	// 四角形の頂点（左上）8
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},	// 四角形の頂点（右上）9
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},	// 四角形の頂点（右下）10
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},	// 四角形の頂点（左下）11
		//左
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)},	// 四角形の頂点（左上）12
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)},	// 四角形の頂点（右上）13
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)},	// 四角形の頂点（右下）14
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)},	// 四角形の頂点（左下）15
		//上
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// 四角形の頂点（左上）16
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// 四角形の頂点（右上）17
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// 四角形の頂点（右下）18
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// 四角形の頂点（左下）19
		//下
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},	// 四角形の頂点（左下）20
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},	// 四角形の頂点（右下）21	
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},	// 四角形の頂点（右上）22
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},	// 四角形の頂点（左上）23

	};

	//頂点の数
	vertexNum_ = vertices_.size();
}

//インデックス情報を準備
void Dice::InitIndexData()
{
	index_ = { 0,1,2, 0,2,3, 4,5,6, 4,6,7, 8,9,10, 8,10,11,
		   12,13,14, 12,14,15, 16,17,18, 16,18,19, 20,21,22, 20,22,23, };

	//インデックス数
	indexNum_ = index_.size();
}