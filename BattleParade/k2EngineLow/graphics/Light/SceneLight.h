#pragma once

namespace nsK2EngineLow {

	//�f�B���N�V�������C�g�̍\����
	struct SDirectionalLight
	{
		//���C�g�̕���
		Vector3 ligDirection;
		////�p�f�B���O
		//float pad;
		//���C�g�̃J���[
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

		//���C�g�̕������擾
		const Vector3& GetligDir() const
		{
			return ligDirection;
		}
		//���C�g�̃J���[���擾
		const Vector4& GetColor() const
		{
			return ligColor;
		}
	};

	//�|�C���g���C�g�̍\����
	struct SPointLight
	{
	private:
		//���C�g�̈ʒu
		Vector3 ptPosition;
		//���C�g�̃J���[
		Vector3 ptColor;
		//���C�g�̉e���͈�
		float ptRange;

	public:
		void SetUp()
		{
			ptPosition = { 0,50,150 };
			ptColor = { 15,0,0 };
			ptRange=100;
		}

		//���W��ݒ�
		void SetPosition(const Vector3& position)
		{
			this->ptPosition = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		//�J���[��ݒ�
		void SetColor(const Vector3& color)
		{
			this->ptColor = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r,g,b });
		}

		//�͈͂�ݒ�
		void SetRange(float range)
		{
			ptRange = range;
		}

		//���W���擾
		const Vector3& GetPosition() const
		{
			return ptPosition;
		}
		//�J���[���擾
		const Vector3& GetColor() const
		{
			return ptColor;
		}
		//�e���͈͂��擾
		const float& GetRange() const
		{
			return ptRange;
		}
	};

	struct SOtherLight
	{
		//�J�����̈ʒu
		Vector3 eyePos;
		
		//����
		Vector3 ambientLight;

	public:
		void Setup()
		{
			//����
			ambientLight.x = 0.1f;
			ambientLight.y = 0.1f;
			ambientLight.z = 0.1f;

			eyePos = g_camera3D->GetPosition();
		}

		//�J�����̈ʒu���擾
		const Vector3& GetEyePos() const
		{
			return eyePos;
		}
		//�������擾
		const Vector3& GetAmbientLight() const
		{
			return ambientLight;
		}
	};

	class SceneLight : public Noncopyable
	{
	public:
		//������
		void Init();
	
	private:
		//�f�B���N�V�������C�g
		SDirectionalLight sdirectionalLight;

		//���̂ق��̃��C�g
		SOtherLight sotherLight;
	};

}