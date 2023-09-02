#pragma once
//ゲームシステム
const float gameWidth = 1920.0f;		//画面の横幅
const float gameHeight = 1080.0f;		//画面の縦幅
const int maxGameTime = 60;				//ゲームの時間
const int maxBlancCount = 180;			//ゲーム前後の隙間の時間(フレーム単位)
const int coinCount = 30;				//コインの枚数
const int AICount = 3;					//CPUキャラの数
const int charaCount = AICount + 1;		//全プレイヤーの数
const int coinGetPoint = 1;				//コインを入手した時の点
const int coinNotGet = 0;				//コインを入手してない時の点
const int fallPenalty = 3;				//落ちた時のペナルティ
const int tackleResultPoint = 3;		//タックルによって増減する得点

//カメラの情報
const Vector3 CameraPos = { 0.0f, 12000.0f, 5000.0f };	//カメラの座標
const Vector3 CameraTargetPos = { 0.0f,0.0f,0.0f };		//カメラの向く座標
const float CameraFar = 15000.0f;						//カメラの遠平面

//キャラ識別番号
const int mychara = 0;					//自キャラの番号
const int firstAI = 1;					//1人目のAI番号
const int secondAI = 2;					//2人目のAI番号
const int thirdAI = 3;					//3人目のAI番号

//キャラ関係の情報
const Vector3 scaleMultiply = { 5.0f,5.0f,5.0f };			//キャラモデルを大きくする倍率
const Vector3 startCharaPos = { 0.0f, 1000.0f, -5000.0f };	//最初の自キャラの場所
const Vector3 startAI1Pos = { 5200.0f,1000.0f,0.0f };		//最初のAI1の場所
const Vector3 startAI2Pos = { -5200.0f,1000.0f,0.0f };		//最初のAI2の場所
const Vector3 startAI3Pos = { 0.0f,1000.0f,5000.0f };		//最初のAI3の場所
const float capsuleRadius = 200.0f;					//当たり判定の半径
const float capsuleHeight = 240.0f;					//当たり判定の高さ
const float controllerRadius = 120.0f;				//物理判定の半径
const float controllerHeight = 240.0f;				//物理判定の高さ
const float gravity = 75.0f;						//重力の強さ
const float jumpPower = 3550.0f;					//ジャンプの強さ
const float moveMultiply = 900.0f;					//移動速度の倍率
const float stickMultiply = -1200.0f;				//スティック入力量への倍率

//タックル関係の情報
const int fullChargeCount = 120;					//タックルが可能になるチャージ量
const int tackleTimeCount = 30;						//タックルをする時間
const int tackleMoveMultiply = 4;					//タックル時の移動速度への倍率
const int stunTime = 90;							//スタン状態の時間
const float tackleMoveWeaken = 1.1;					//被タックル後の移動速度の減衰率
const float receiveTackleMoveMultiply = 10000.0f;	//被タックル時の移動速度への倍率

//アニメーションの番号
const int animation_idle = 0;		//立ちアニメーションステート
const int animation_walk = 1;		//歩きアニメーションステート
const int animation_fall = 2;		//落下アニメーションステート
const int animation_jump = 3;		//ジャンプアニメーションステート
const int animation_run = 4;		//走りアニメーションステート

//UI関係の情報
const Vector2 timePos = { -50.0f,500.0f };				//時間を表示する座標
const Vector2 charaPointPos = { -900.0f,500.0f };		//プレイヤーの得点を表示する座標
const Vector2 AI1PointPos = { 800.0f,500.0f };			//AI1の得点を表示する座標
const Vector2 AI2PointPos = { -900.0f,-425.0f };		//AI2の得点を表示する座標
const Vector2 AI3PointPos = { 800.0f,-425.0f };			//AI3の得点を表示する座標

//タイトル画面の情報
const Vector3 startButtonPos = { 0.0f,100.0f,0.0f };	//ゲーム開始のボタンの座標
const Vector3 operationButtonPos = { 0.0f,0.0f,0.0f };	//操作説明のボタンの座標
const int startButtonNumber = 0;						//ゲーム開始のボタンを表す番号
const int operationButtonNumber = 1;					//操作説明のボタンを表す番号
const float cursorWidth = 150.0f;						//カーソルの横幅
const float cursorHeight = 130.0f;						//カーソルの縦幅

//フェードの情報
const int fadeOutFrag = 0;		//フェードアウトをするフラグ
const int fadeInFrag = 1;		//フェードインをするフラグ
const int fadeIdleFlag = 2;		//フェード待機状態のフラグ
const int fadeTime = 60;		//フェードの時間

//結果画面の情報
const Vector2 resultRankStartPos[charaCount] = {
	{990.0f, 350.0f},		//ランキング1位の人を表示する座標
	{990.0f, 100.0f},		//ランキング2位の人を表示する座標
	{990.0f,-100.0f},		//ランキング3位の人を表示する座標
	{990.0f,-350.0f}		//ランキング4位の人を表示する座標
};
const Vector3 pointBackStartPos[charaCount] = {
	{1000.0f,  350.0f, 0.0f},
	{1000.0f,  100.0f, 0.0f},
	{1000.0f, -100.0f, 0.0f},
	{1000.0f, -350.0f, 0.0f}
};