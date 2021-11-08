#pragma once
#include<DxLib.h>
class Unit;
class Camera
{
public:

	static constexpr float HEIGHT = 300.0f;
	static constexpr float DIS_TARGET_TO_CAMERA = 500.0f;

	static constexpr float  DIS_TARGET_TO_UNIT = 300.0f;

	Camera();

	void Init(void);
	void Update(void);

	void SetBeforeDraw(void);

	void Draw(void);
	void Release(void);

	void SetUnit(Unit* unit);

	VECTOR GetPos(void);

	VECTOR GetAngles(void);
	VECTOR GetTargetPos(void);

	VECTOR Relese(void);

private:
	Unit* mUnit;

	//カメラの位置
	VECTOR mPos;

	//カメラ角度(rad)
	VECTOR mAngles;

	VECTOR mTargetPos;
};

