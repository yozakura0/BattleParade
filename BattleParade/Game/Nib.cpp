#include "stdafx.h"
#include "Nib.h"

Nib::Nib()
{
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	srand((unsigned int)time(NULL));

	floarApos = { -900.0f,0.0f,0.0f };
	floarBpos = { 900.0f,0.0f,0.0f };

	AnimationClips[Afall].Load("Assets/animData/nib/move.tka");
	AnimationClips[Afall].SetLoopFlag(false);
	AnimationClips[Bfall].Load("Assets/animData/nib/move.tka");
	AnimationClips[Bfall].SetLoopFlag(false);

	frameA.SetPosition(floarApos);
	frameB.SetPosition(floarBpos);
	frameA.Init("Assets/modelData/nib/frame.tkm");
	frameB.Init("Assets/modelData/nib/frame.tkm");

	A.SetPosition(floarApos);
	B.SetPosition(floarBpos);
	A.Init("Assets/modelData/nib/nib_A.tkm");
	B.Init("Assets/modelData/nib/nib_B.tkm");

	frameA.Update();
	frameB.Update();
	A.Update();
	B.Update();

	frameObjectA.CreateFromModel(frameA.GetModel(), frameA.GetModel().GetWorldMatrix());
	frameObjectB.CreateFromModel(frameB.GetModel(), frameB.GetModel().GetWorldMatrix());
	floarA.CreateFromModel(A.GetModel(), A.GetModel().GetWorldMatrix());
	floarB.CreateFromModel(B.GetModel(), B.GetModel().GetWorldMatrix());
	/*floarA.Create({ 1000.0f,1000.0f,1000.0f });
	floarB.Create({ 1000.0f,1000.0f,1000.0f });*/

	//floarB.Release();
	sw.Start();
	isStart = true;
}

Nib::~Nib()
{

}

void Nib::Update()
{
	timeFrame = sw.GetElapsed();
	g_camera3D->SetPosition({ 0.0f, 3000.0f, -2000.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });

	float angle = g_camera3D->GetViewAngle();
	angle = 0.7f;
	g_camera3D->SetViewAngle(angle);

	Timer();
	A.Update();
	B.Update();
}

void Nib::Timer()
{
	if (now < 0.0f) {
		sw.Stop();		//Œv‘ªI—¹
		isStop = true;
		now = 0;
	}

	if (isStart == true) {
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"TIME  %.*f\nwait %.*f", 0, now, 0, wait);
		fr.SetText(wcsbuf);
		fr.SetPosition({ 0.0f,500.0f });
		now -= 1.0f * (1.0f / 60.0f);

		wchar_t wcsbuf2[256];
		swprintf_s(wcsbuf2, 256, L"ROUND  %d", round);
		ROUND.SetText(wcsbuf2);
		ROUND.SetPosition({ 400.0f,500.0f });
	}

	if (isStop == true)
	{
		if (wait == 1) {
			judge = rand() % 2;
		}


		if (wait == 200) {
			switch (judge)
			{
			case 0:
				A.PlayAnimation(Afall);
				floarA.Release();
				break;
			case 1:
				B.PlayAnimation(Bfall);
				floarB.Release();
				break;
			}
		}
		


		fr.SetText(L"STOP");
		wait++;
		if (wait > 500)
		{
			switch (judge)
			{
			case 0:
				floarA.CreateFromModel(A.GetModel(), A.GetModel().GetWorldMatrix());
				break;
			case 1:
				floarB.CreateFromModel(B.GetModel(), B.GetModel().GetWorldMatrix());
				break;
			}
			round++;
			isStop = false;
			wait = 0;
			now = 3.0f;
		}
	}
}

void Nib::Render(RenderContext& rc)
{
	frameA.Draw(rc);
	frameB.Draw(rc);
	A.Draw(rc);
	B.Draw(rc);
	fr.Draw(rc);
	ROUND.Draw(rc);
}