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

	//スポットライト用のデータ
	//スポットライトの位置
	float3 spPosition;
	//スポットライトのカラー
	float3 spColor;
	//スポットライトの射出範囲
	float spRange;
	//スポットライトの射出方向
	float3 spDirection;
	//スポットライトの射出角度
	float spAngle;

	//半球ライト用のデータ
	//照り返しのライト
	float3 groundColor;
	//天球ライト
	float3 skyColor;
	//地面の法線
	float3 groundNormal;

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
	//float3 tangent	: TANGENT;		//接ベクトル
	//float3 biNormal	: BINORMAL;		//従ベクトル
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;		//法線
	//float3 tangent		: TANGENT;		//接ベクトル
	//float3 biNormal		: BINORMAL;		//従ベクトル
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos		: TEXCOORD1;
	float3 normalInView	: TEXCOORD2;	//カメラ空間の法線
};

//関数を宣言
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float3 CalcLigFromSpotLight(SPSIn psIn);
float3 CalcLigFromPointLight(SPSIn psIn);
float3 CalcLigFromDirectionLight(SPSIn psIn);

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
//Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
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

	/*psIn.tangent = normalize(mul(mWorld, vsIn.tangent));
	psIn.biNormal = normalize(mul(mWorld, vsIn.biNormal));*/

	psIn.uv = vsIn.uv;

	//カメラ空間の法線を求める
	psIn.normalInView = mul(mView, psIn.normal);

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
	////法線マップからタンジェントスペースの法線をサンプリング
	//float3 localNormal = g_normalMap.Sample(g_sampler,psIn.uv).xyz;
	////タンジェントスペースの法線を0～1の範囲から-1～1の範囲に復元
	//localNormal = (localNormal - 0.5f) * 2.0f;

	////タンジェントスペースの法線をワールドスペースに変換
	//normal = psIn.tangent * localNormal.x
	//	+ psIn.biNormal * localNormal.y
	//	+ normal * localNormal.z;

	//ディレクションライトによるライティングを計算
	float3 directionLig = CalcLigFromDirectionLight(psIn);

	//ポイントライトによるライティングを計算
	float3 pointLig = CalcLigFromPointLight(psIn);

	//スポットライトによるライティングを計算
	//float3 spotLig = CalcLigFromSpotLight(psIn);

	//サーフェイスの法線と光の入射方向に依存するリムの強さを求める
	float power1 = 1.0f - max(0.0f, dot(dirDirection, psIn.normal));

	//サーフェイスの法線と視線の方向に依存するリムの強さを求める
	float power2 = 1.0f - max(0.0f, psIn.normalInView.z * -1.0f);

	//最終的なリムの強さを求める
	float limPower = power1 * power2;
	limPower = pow(limPower, 1.3f);

	//リムライトのカラーを計算
	float3 limColor = limPower * dirColor;

	//サーフェイスの法線と地面の法線との内積を計算
	float t = dot(psIn.normal, groundNormal);

	//内積の結果を0～1の範囲に変換する
	t = (t + 1.0f) / 2.0f;

	//地面色と天球色を補完率tで線形補完
	float3 hemiLight = lerp(groundColor, skyColor, t);

	//ライトの効果を合わせる
	float3 lig = directionLig + pointLig + ambientLight/* + spotLig*/;
	lig += limColor + hemiLight;

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
	float3 specularLig = lightColor * t;

	////スペキュラマップからスペキュラ反射の強さをサンプリング
	//float specPower = g_specularMap.Sample(g_sampler, psIn.uv).r;

	////鏡面反射の強さを鏡面反射光に乗算
	//specularLig *= specPower;

	return specularLig;
}

//スポットライトによる反射光を計算
float3 CalcLigFromSpotLight(SPSIn psIn)
{
	//このサーフェイスに入射しているスポットライトの光の向きを計算する
	float3 ligDir = psIn.worldPos - spPosition;

	//正規化して大きさ1のベクトルにする
	ligDir = normalize(ligDir);

	//減衰なしの拡散反射光を計算する
	float3 diffSpot = CalcLambertDiffuse(
		//ライトの方向
		ligDir,
		//ライトのカラー
		spColor,
		//サーフェイスの法線
		psIn.normal
	);

	//減衰なしの鏡面反射光を計算する
	float3 specSpot = CalcPhongSpecular(
		//ライトの方向
		ligDir,
		//ライトのカラー
		spColor,
		//サーフェイスのワールド座標
		psIn.worldPos,
		//サーフェイスの法線
		psIn.normal
	);

	//距離による影響率を計算する
	//ポイントライトとの距離を計算する
	float3 distance = length(psIn.worldPos - spPosition);

	//影響率は距離に比例して小さくなっていく
	float affect = 1.0f - 1.0f / spRange * distance;

	//影響力がマイナスにならないように補正をかける
	if (affect < 0.0f)
	{
		affect = 0.0f;
	}

	//影響の仕方を指数関数的にする
	affect = pow(affect, 3.0f);

	//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
	diffSpot *= affect;
	specSpot *= affect;

	//入射光と射出方向の角度を求める
	float angle = dot(ligDir, spDirection);

	angle = abs(acos(angle));

	//角度に比例して小さくなっていく影響率を計算する
	affect = 1.0f - 1.0f / spAngle * angle;

	//影響率がマイナスにならないよう補正する
	if (affect < 0.0f)
	{
		affect = 0.0f;
	}

	//影響の仕方を指数関数的にする
	affect = pow(affect, 0.5f);

	//角度による影響率を反射光に乗算して、影響を弱める
	diffSpot *= affect;
	specSpot *= affect;

	return diffSpot + specSpot;
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