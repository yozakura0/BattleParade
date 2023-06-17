#pragma once

namespace nsK2EngineLow {

	//ディレクションライトの構造体
	struct SDirectionalLight
	{
		//ライトの方向
		Vector3 ligDirection;
		////パディング
		//float pad;
		//ライトのカラー
		Vector4 ligColor;

		void Setup()
		{
			ligColor.x = 1.2f;
			ligColor.y = 1.2f;
			ligColor.z = 1.2f;

			ligDirection.x = 1.0f;
			ligDirection.y = -1.0f;
			ligDirection.z = -1.0f;
			ligDirection.Normalize();
		}

		//ライトの方向を取得
		const Vector3& GetligDir() const
		{
			return ligDirection;
		}
		//ライトのカラーを取得
		const Vector4& GetColor() const
		{
			return ligColor;
		}
	};

	//ポイントライトの構造体
	struct SPointLight
	{
	private:
		//ライトの位置
		Vector3 ptPosition;
		//ライトのカラー
		Vector3 ptColor;
		//ライトの影響範囲
		float ptRange;

	public:
		void SetUp()
		{
			ptPosition = { 0,50,150 };
			ptColor = { 15,0,0 };
			ptRange=100;
		}

		//座標を設定
		void SetPosition(const Vector3& position)
		{
			this->ptPosition = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		//カラーを設定
		void SetColor(const Vector3& color)
		{
			this->ptColor = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r,g,b });
		}

		//範囲を設定
		void SetRange(float range)
		{
			ptRange = range;
		}

		//座標を取得
		const Vector3& GetPosition() const
		{
			return ptPosition;
		}
		//カラーを取得
		const Vector3& GetColor() const
		{
			return ptColor;
		}
		//影響範囲を取得
		const float& GetRange() const
		{
			return ptRange;
		}
	};

	struct SOtherLight
	{
		//カメラの位置
		Vector3 eyePos;
		
		//環境光
		Vector3 ambientLight;

	public:
		void Setup()
		{
			//環境光
			ambientLight.x = 0.1f;
			ambientLight.y = 0.1f;
			ambientLight.z = 0.1f;

			eyePos = g_camera3D->GetPosition();
		}

		//カメラの位置を取得
		const Vector3& GetEyePos() const
		{
			return eyePos;
		}
		//環境光を取得
		const Vector3& GetAmbientLight() const
		{
			return ambientLight;
		}
	};

	class SceneLight : public Noncopyable
	{
	public:
		//初期化
		void Init();
	
	private:
		//ディレクションライト
		SDirectionalLight sdirectionalLight;

		//そのほかのライト
		SOtherLight sotherLight;
	};

}