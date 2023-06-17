/*!
 * @brief	シンプルなモデルシェーダー。
 */


////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

//ライトのデータを受け取る定数バッファ
cbuffer DirectionLightCb : register(b1)
{
	//ディレクションライト用のデータ
	//ライトの方向
	float3 dirDirection;
	//ライトのカラー
	float3 dirColor;
	
	//ポイントライト用のデータ
	//ポイントライトの位置
	float3 ptPosition;
	//ポイントライトのカラー
	float3 ptColor;
	//ポイントライトの影響範囲
	float ptRange;

	//視点の位置
	float3 eyePos;
	float3 ambientLight;
}

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos		: TEXCOORD1;
};

//関数を宣言
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float3 CalcLigFromPointLight(SPSIn psIn);
float3 CalcLigFromDirectionLight(SPSIn psIn);

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
	psIn.worldPos = vsIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	//頂点法線をピクセルシェーダーに渡す
	psIn.normal = mul(mWorld, vsIn.normal);

	psIn.uv = vsIn.uv;

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
	//ディレクションライトによるライティングを計算
	float3 directionLig = CalcLigFromDirectionLight(psIn);

	//ポイントライトによるライティングを計算
	float3 pointLig = CalcLigFromPointLight(psIn);

	//ライトの効果を合わせる
	float3 lig = directionLig + pointLig + ambientLight;

	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	//最終出力カラーに光を乗算
	albedoColor.xyz *= lig;

	return albedoColor;
}

//拡散反射光を計算する
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
	//ピクセルの法線とライトの方向の内積を計算する
	float t = dot(normal, lightDirection) * -1.0f;

	//内積の値を0以上の値にする
	t = max(0.0f, t);

	//拡散反射光を計算
	return lightColor * t;
}
//鏡面反射光を計算する
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
	//反射ベクトルを求める
	float3 refVec = reflect(lightDirection, normal);

	//光が当たったサーフェイスから視点に伸びるベクトルを求める
	float3 toEye = eyePos - worldPos;
	toEye = normalize(toEye);

	//鏡面反射の強さを求める
	float t = dot(refVec, toEye);

	//鏡面反射の強さを0以上の値にする
	t = max(0.0f, t);

	//鏡面反射の強さを絞る
	t = pow(t, 5.0f);

	//鏡面反射光を求める
	return lightColor * t;
}

//ポイントライトによる反射光を計算
float3 CalcLigFromPointLight(SPSIn psIn)
{
	//このサーフェイスに入射しているポイントライトの光の向きを計算する
	float3 ligDir = psIn.worldPos - ptPosition;

	//正規化して大きさ1のベクトルにする
	ligDir = normalize(ligDir);

	//減衰なしの拡散反射光を計算する
	float3 diffPoint = CalcLambertDiffuse(
		//ライトの方向
		ligDir,
		//ライトのカラー
		ptColor,
		//サーフェイスの法線
		psIn.normal
	);

	//減衰なしの鏡面反射光を計算する
	float3 specPoint = CalcPhongSpecular(
		//ライトの方向
		ligDir,
		//ライトのカラー
		ptColor,
		//サーフェイスのワールド座標
		psIn.worldPos,
		//サーフェイスの法線
		psIn.normal
	);

	//距離による影響率を計算する
	//ポイントライトとの距離を計算する
	float3 distance = length(psIn.worldPos - ptPosition);

	//影響率は距離に比例して小さくなっていく
	float affect = 1.0f - 1.0f / ptRange * distance;

	//影響力がマイナスにならないように補正をかける
	if (affect < 0.0f)
	{
		affect = 0.0f;
	}

	//影響の仕方を指数関数的にする
	affect = pow(affect, 3.0f);

	//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
	diffPoint *= affect;
	specPoint *= affect;

	return diffPoint + specPoint;
}

//ディレクションライトによる反射光を計算
float3 CalcLigFromDirectionLight(SPSIn psIn)
{
	//拡散反射光を計算する
	float3 diffDirection = CalcLambertDiffuse(dirDirection, dirColor, psIn.normal);

	//鏡面反射光を計算する
	float3 specDirection = CalcPhongSpecular(dirDirection, dirColor, psIn.worldPos, psIn.normal);

	return diffDirection + specDirection;
}