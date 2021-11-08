#include<DxLib.h>
#include "Stage.h"

Stage::Stage(SceneManager* manager)
{
	mSceneManager = manager;
}

void Stage::Init(void)
{
	mModel = MV1LoadModel("Model/Stage.mv1");
	mPos = { 0.0f,-100.0f,0.0f };

	//モデルの事前設定(座標)
	MV1SetPosition(mModel, mPos);

}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{

	//
	VECTOR pos1 = { 0.0f,0.0f,0.0f };
	VECTOR pos2 = { 0.0f,100.0f,0.0f };



	//XYZのグリッド線
	float LEN = 500;
	//X

	for (int z = 0; z < 10; z++)
	{
		pos1 = { 0.0f,0.0f,0.0f };
		DrawLine3D({ -LEN,0.0f,-LEN+(z*100)}, 
			{ LEN,0.0f,-LEN+(z * 100) },
			0xff0000);
	}
	
	


	//Y
	DrawLine3D({ 0,LEN,0 }, { 0,-LEN,0 }, 0x00ff00);

	//Z
	for (int x = 0; x < 10; x++)
	{
		DrawLine3D({ -LEN + (x * 100),0.0f,-LEN },
			{ -LEN + (x * 100),0.0f,LEN },
			0x0000ff);
	}


	MV1DrawModel(mModel);

}

void Stage::Release(void)
{
	MV1DeleteModel(mModel);
}
