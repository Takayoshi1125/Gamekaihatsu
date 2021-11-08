#include "DxLib.h"
#include"AsoUtility.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include"Camera.h"
#include"Stage.h"
#include"Unit.h"
#include"Enemy.h"
#include"RollBall.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
}

void TitleScene::Init(void)
{
	mStage = new Stage(mSceneManager);
	mStage->Init();

	mUnit = new Unit(mSceneManager);
	mUnit->Init();

	mEnemy = new Enemy(mSceneManager,mUnit);
	mEnemy->Init();

	mRollBall = new RollBall(mSceneManager, mUnit);
	mRollBall->Init();

	mSceneManager->GetCamera()->SetUnit(mUnit);
}

void TitleScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::TITLE, true);
	}
	mStage->Update();
	mUnit->Update();
	mEnemy->Update();
	mRollBall->Update();
}

void TitleScene::Draw(void)
{
	mStage->Draw();

	mUnit->Draw();

	mEnemy->Draw();

	mRollBall->Draw();

	DrawDebug();
	
}

void TitleScene::DrawDebug(void)
{
	Camera* camera = mSceneManager->GetCamera();

	VECTOR pos = camera->GetPos();
	VECTOR angles = camera->GetAngles();
	
	
	/*DrawFormatStringF(0, 0, 0xffffff, "1.0f,1.0f,%f",camera->GetPos());

	DrawFormatStringF(0, 16, 0xffffff, "%d,%d,%d", camera->GetAngles());*/

	pos = mUnit->GetPos();
	angles = mUnit->GetAngle();

	//DrawFormatString(0, 50, 0xffffff,
	//	"キャラ座標:(%.1f,%.1f,%.1f)",
	//	pos.x, pos.y, pos.z);

	//DrawFormatString(0, 70, 0xffffff,
	//	"キャラ座標:(%.1f,%.1f,%.1f)",
	//	AsoUtility::Rad2Deg(angles.x),
	//	AsoUtility::Rad2Deg(angles.y),
	//	AsoUtility::Rad2Deg(angles.z)
	//);


	//pos = mUnit->GetPos();
	//angles = mUnit->GetAngle();

	//DrawFormatString(0, 50, 0xffffff,
	//	"キャラ座標:(%.1f,%.1f,%.1f)",
	//	pos.x, pos.y, pos.z);

	//DrawFormatString(0, 70, 0xffffff,
	//	"キャラ座標:(%.1f,%.1f,%.1f)",
	//	AsoUtility::Rad2Deg(angles.x),
	//	AsoUtility::Rad2Deg(angles.y),
	//	AsoUtility::Rad2Deg(angles.z)
	//);

	//VECTOR uPos = mUnit->GetPos();
	//VECTOR bPos = mRollBall->GetPos();

	//float rad = atan2(bPos.x-uPos.x, bPos.z-uPos.z);
	//float deg = AsoUtility::Rad2Deg(rad);

	//DrawFormatString(0, 130, 0xffffff, "ボール");
	//DrawFormatString(0, 150, 0xffffff, "座標:%.2f,%.2f,%.2f",bPos.x,bPos.y,bPos.z);
	//DrawFormatString(0, 170, 0xffffff, "角度:%.2f",deg);

	////キャラの向いている方向を基準にした球体の角度
	//VECTOR uAngles = mUnit->GetAngle();
	//float viewRad = rad - uAngles.y;
	//float viewDeg = AsoUtility::Rad2Deg(viewRad);
	//viewDeg = AsoUtility::DegIn360(viewDeg);
	//DrawFormatString(0, 190, 0xffffff, "角度(対ユニット):%.2f", viewDeg);

}

void TitleScene::Release(void)
{
	mStage->Release();
	delete mStage;

	mUnit->Release();
	delete mUnit;

	mEnemy->Release();
	delete mEnemy;

	mRollBall->Release();
	delete mRollBall;
}
