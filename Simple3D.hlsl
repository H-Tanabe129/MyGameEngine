//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D	g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matW;	//ワールド行列
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
	float2 uv     : TEXCOORD;		//UV座標
	float4 color	: COLOR;	//色（明るさ）
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
	outData.uv = uv;

	//法線を回転
	normal = mul(normal, matW);

	float4 light = float4(1, 0.8, -0.3, 0);
	light = normalize(light);
	outData.color = clamp(dot(normal, light),0,1);

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0, 1.0, 1.0, 0.0); //RGB
	float4 ambientSource = float4(0.5, 0.5, 0.5, 1.0);
	//    return lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
		//               色↓
		float4 diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
		float4 ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientSource;
		return (diffuse + ambient); //g_texture.Sample(g_sampler, inData.uv);
	//return g_texture.Sample(g_sampler, inData.uv) * inData.color;
}