#include "stdafx.h"
#include "system/system.h"

#include "ShowTest.h"

//#include "testModel.h"
//#include "RaceStage.h"
//#include "Car.h"
//#include "RaceCamera.h"
//
//#include "Nib.h"
//#include "GameSelect.h"
//
//#include "Roll.h"
//
//#include "MainCamera.h"
//#include "Player.h"

#include "Coin.h"
#include "CoinTitle.h"
#include "Fade.h"

// K2EngineLow�̃O���[�o���A�N�Z�X�|�C���g�B
K2EngineLow* g_k2EngineLow = nullptr;
SDirectionalLight sdirectionalLight;
SPointLight spointLight;
SSpotLight sspotLight;
SOtherLight sotherLight;

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// �Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	
	// k2EngineLow�̏������B
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);
	g_camera3D->SetPosition({ 0.0f, 100.0f, -200.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });

	//���C�g�̃f�[�^���
	/*sdirectionalLight.Setup();
	spointLight.SetUp();
	sspotLight.SetUp();
	sotherLight.Setup();*/

	//NewGO<testModel>(0, "tm");
	//NewGO<RaceStage>(1, "Rstage");
	//NewGO<Car>(2, "car");
	//NewGO<RaceCamera>(3, "racecamera");
	/*NewGO<Nib>(0, "nib");*/
	//NewGO<GameSelect>(0, "select");
	//NewGO<Roll>(0, "roll");
	//NewGO<MainCamera>(0, "maincamera");
	/*NewGO<Player>(1, "player");*/

	//NewGO<ShowTest>(0);

	NewGO<CoinTitle>(0, "coinTitle");
	NewGO<Fade>(5, "fade");

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		// �t���[���̊J�n���ɌĂяo���K�v�����鏈�������s
		g_k2EngineLow->BeginFrame();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�������Ăяo���B
		g_k2EngineLow->ExecuteUpdate();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̕`�揈�����Ăяo���B
		g_k2EngineLow->ExecuteRender();

		// �f�o�b�O�`�揈�������s����B
		g_k2EngineLow->DebubDrawWorld();

		// �t���[���̏I�����ɌĂяo���K�v�����鏈�������s�B
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}

