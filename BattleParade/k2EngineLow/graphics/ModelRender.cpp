#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow 
{

	ModelRender::ModelRender()
	{
	}

	ModelRender::~ModelRender()
	{

	}

	/*void ModelRender::SetupVertexShaderEntryPointFunc(ModelInitData& modelInitData)
	{
		modelInitData.m_vsSkinEntryPointFunc = "VSMainUsePreComputedVertexBuffer";
		modelInitData.m_vsEntryPointFunc = "VSMainUsePreComputedVertexBuffer";
	}*/

	void ModelRender::Init(
		const char* filePath
		/*AnimationClip* animationClips = nullptr,
		int numAnimationClips = 0,
		EnModelUpAxis enModelUpAxis = enModelUpAxisZ*/
	)
	{
		m_modelInitData.m_tkmFilePath = filePath;
		m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";

		//SetupVertexShaderEntryPointFunc(m_modelInitData);
		//�X�P���g����������
		//InitSkeleton(filePath);
		//�A�j���[�V������������
		//InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
		
		m_Model.Init(m_modelInitData);
	}

	//void ModelRender::InitSkeleton(const char* filepath)
	//{
	//	//�X�P���g���̃f�[�^��ǂݍ���
	//	std::string skeletonFilePath = filepath;
	//	int pos = (int)skeletonFilePath.find(".tkm");
	//	skeletonFilePath.replace(pos, 4, ".tks");
	//	//m_skeleton.Init(skeletonFilePath.c_str());
	//}

	/*void ModelRender::InitAnimation(AnimationClip* animationClips = nullptr,int numAnimationClips = 0,EnModelUpAxis enModelUpAxis = enModelUpAxisZ)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr)
		{
			m_animation.Init(
				m_skeleton,
				m_animationClips,
				numAnimationClips
			);
		}
	}*/

	void ModelRender::UpdateWorldMatrixInModes()
	{
		m_Model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	}

	void ModelRender::Update()
	{
		UpdateWorldMatrixInModes();

		if (m_skeleton.IsInited())
		{
			m_skeleton.Update(m_Model.GetWorldMatrix());
		}

		//m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		//�ʏ�`��
		//g_renderingEngine->AddRenderObject(this);

		m_Model.Draw(rc);
	}
}