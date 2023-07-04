#include "stdafx.h"
#include "system/system.h"

#include "testModel.h"
#include "RaceStage.h"
#include "Car.h"
#include "RaceCamera.h"

#include "Nib.h"
#include "GameSelect.h"

#include "Roll.h"

#include "MainCamera.h"
#include "Player.h"


// K2EngineLowのグローバルアクセスポイント。
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// メイン関数
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	
	// k2EngineLowの初期化。
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);
	g_camera3D->SetPosition({ 0.0f, 100.0f, -200.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });

	//NewGO<testModel>(0, "tm");
	//NewGO<RaceStage>(1, "Rstage");
	//NewGO<Car>(2, "car");
	//NewGO<RaceCamera>(3, "racecamera");
	NewGO<Nib>(0, "nib");
	//NewGO<GameSelect>(0, "select");
	//NewGO<Roll>(0, "roll");
	//NewGO<MainCamera>(0, "maincamera");
	NewGO<Player>(1, "player");

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		// フレームの開始時に呼び出す必要がある処理を実行
		g_k2EngineLow->BeginFrame();

		// ゲームオブジェクトマネージャーの更新処理を呼び出す。
		g_k2EngineLow->ExecuteUpdate();

		// ゲームオブジェクトマネージャーの描画処理を呼び出す。
		g_k2EngineLow->ExecuteRender();

		// デバッグ描画処理を実行する。
		g_k2EngineLow->DebubDrawWorld();

		// フレームの終了時に呼び出す必要がある処理を実行。
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}

