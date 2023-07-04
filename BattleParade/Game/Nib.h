#pragma once
class Nib:public IGameObject
{
public:
	Nib();
	~Nib();

	void Update();

	void Timer();

	void Render(RenderContext& rc);

	PhysicsStaticObject floarA;
	//BoxCollider floarA;
	PhysicsStaticObject floarB;
	//BoxCollider floarB;
	PhysicsStaticObject frameObjectA;
	PhysicsStaticObject frameObjectB;

	ModelRender A;
	ModelRender B;
	ModelRender frameA;
	ModelRender frameB;
	bool isStop = false;
	bool isStart = false;

	enum fallclip
	{
		Afall,
		Bfall,
		no
	};

	AnimationClip AnimationClips[no];

private:
	Vector3 floarApos;
	Vector3 floarBpos;

	float timeFrame;
	Stopwatch sw;
	FontRender fr;
	FontRender ROUND;
	float now=10.0f;
	float wait;
	int round=1;
	int judge;
};

