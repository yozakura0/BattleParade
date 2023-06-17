#pragma once

//#include "geometry/"
#include "Light/SceneLight.h"

namespace nsK2EngineLow {

	class RenderingEngine;
	//class SceneLight;

	struct DirectionalLight
	{
		//ライトの方向
		Vector3 ligDirection;
		//パディング
		float pad;
		//ライトのカラー
		Vector4 ligColor;
	};

	struct PointLight
	{
		//ライトの位置
		Vector3 ptPosition;
		float pad2;
		//ライトのカラー
		Vector3 ptColor;
		//ライトの影響範囲
		float ptRange;
	};

	struct Light
	{
		//ディレクションライトの配列(最大1個置ける)
		DirectionalLight directionalLight;
		//ポイントライトの配列
		PointLight pointLight;

		//カメラの位置
		Vector3 eyePos;

		//環境光
		Vector3 ambientLight;
	};

	class ModelRender :public IRenderer
	{
	public:
		ModelRender();
		~ModelRender();

		//モデルレンダーの初期化
		void Init(
			//ファイルのパス
			const char* filePath
			////アニメーションクリップ
			//AnimationClip* animationClips = nullptr,
			////アニメーションクリップの数
			//int numAnimationClips = 0,
			////モデルの上方向の設定
			//EnModelUpAxis enModelUpAxis = enModelUpAxisZ
		);

		//更新処理
		void Update();

		//描画処理
		void Draw(RenderContext& rc);

		//アニメーションの再生
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			//m_animation.Play(animNo, interpolateTime);
		}

		//座標、回転、大きさを全て設定
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}

		//座標の設定
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		//座標の設定
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		//回転の設定
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		//拡大率の設定
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		//拡大率の設定
		void SetScale(float x, float y, float z)
		{
			SetScale({ x,y,z });
		}

	private:
		////スケルトンの初期化
		//void InitSkeleton(
		//	//ファイルパス
		//	const char* filepath
		//);

		////アニメーションの初期化
		//void InitAnimation(
		//	//アニメーションクリップ
		//	//AnimationClip* animationClips = nullptr,
		//	//アニメーションクリップの数
		//	int numAnimationClips = 0
		//	//モデルの上向き
		//	//EnModelUpAxis enModelUpAxis = enModelUpAxisZ
		//);

		//各種モデルのワールド座標を更新する
		void  UpdateWorldMatrixInModes();

		//各種モデルの頂点シェーダーのエントリーポイントを設定
		//void SetupVertexShaderEntryPointFunc(ModelInitData& modelInitData);

	private:
		//アニメーションクリップ
		//AnimationClip* m_animationClips = nullptr;
		//アニメーションクリップの数
		//int m_numAnimationClips = 0;
		//座標
		Vector3 m_position = Vector3::Zero;
		//回転
		Quaternion m_rotation = Quaternion::Identity;
		//拡大率
		Vector3 m_scale = Vector3::One;
		//アニメーション
		//Animation m_animation;
		//モデル
		Model m_Model;
		//モデルの初期化データ
		ModelInitData m_modelInitData;
		//フォワードレンダリングの描画パスで描画されるモデル
		//Model m_forwardRenderModel;
		//RenderToGBufferで描画されるモデル
		//Model m_renderToGBufferModel;
		//スケルトン
		Skeleton m_skeleton;
		//アニメーションの再生速度
		//float m_animationSpeed = 1.0f;
		//ジオメトリ情報
		//std::vector<Gemo>

		//SceneLight sceneLight;
		
		//シーンライトのライト
		/*SLight slight;*/

		//シーンライトのディレクションライト
		SDirectionalLight sdirectionalLight;

		//シーンライトのポイントライト
		SPointLight spointLight;

		//シーンライトのそのほかライト
		SOtherLight sotherLight;

		//モデルレンダー内のディレクションライト
		//DirectionalLight directionalLight;

		//ライト
		Light light;
	};
}

