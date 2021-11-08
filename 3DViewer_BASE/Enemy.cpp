#include <cmath>
#include"AsoUtility.h"
#include"Unit.h"
#include "Enemy.h"

Enemy::Enemy(SceneManager* manager,Unit* unit)
{
    mSceneManager = manager;
    mUnit = unit;
}

void Enemy::Init(void)
{
    mModel = MV1LoadModel("Model/Human.mv1");
    mPos = {200.0f,0.0f,400.0f };
    mAngles = { 0.0f,(float)AsoUtility::Deg2Rad(30.0f),0.0f };
    mAnglesLocal = { 0.0f,(float)AsoUtility::Deg2Rad(180.0f),0.0f };

    MV1SetPosition(mModel, mPos);

    VECTOR angle = mAngles;
    angle.x += mAnglesLocal.x;
    angle.y += mAnglesLocal.y;
    angle.z += mAnglesLocal.z;


    MV1SetRotationXYZ(mModel, angle);

    mIsNotice = false;

}

void Enemy::Update(void)
{
    mIsNotice = false;
    

    float movePow = 5.0f;
    float rodRad = 0.0f;

    VECTOR uPos = mUnit->GetPos();


    VECTOR angle = mAngles;
    angle.x += mAnglesLocal.x;
    angle.y += mAnglesLocal.y;
    angle.z += mAnglesLocal.z;
    MV1SetRotationXYZ(mModel, angle);

   

    //視野範囲に入っているか判断
    float disX = uPos.x - mPos.x;
    float disZ = uPos.z - mPos.z;
    float distance = std::pow(disX, 2) + std::pow(disZ, 2);

   if (distance <= std::pow(VIEW_RANGE, 2))
    {
        //視野角の条件式

    //絶対(ワールドグローバル)角度
        float rad = atan2(uPos.x - mPos.x, uPos.z - mPos.z);
        float deg = AsoUtility::Rad2Deg(rad);

        float viewRad = rad - mAngles.y;
        float viewDeg = AsoUtility::Rad2Deg(viewRad);
        viewDeg = AsoUtility::DegIn360(viewDeg);

        //視野角の条件式
        if (viewDeg <= VIEW_ANGLE || viewDeg >= (360.0f - VIEW_ANGLE))
        {
            //mAngles.y=
            mIsNotice = true;
            mPos.x += sinf(rodRad) * movePow;
            mPos.z += cosf(rodRad) * movePow;
        }
    }

   MV1SetPosition(mModel, mPos);
}

void Enemy::Draw(void)
{
    if (mIsNotice)
    {
        MV1SetMaterialDifColor(mModel, 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
    }
    else
    {
        MV1SetMaterialDifColor(mModel, 0, GetColorF(0.5f, 0.5f, 0.0f, 0.5f));
    }

    MV1DrawModel(mModel);

    float viewRad = AsoUtility::Deg2Rad(VIEW_ANGLE);

    //視野を描画
    VECTOR pos0, pos1, pos2,pos3;

    //mAngles.y⇒角度⇒方向

    float x1 = sin(mAngles. y);
    float z1 = cos(mAngles.y);

    float x2 = sin(mAngles.y-viewRad);
    float z2 = cos(mAngles.y-viewRad);

    float x3 = sin(mAngles.y + viewRad);
    float z3 = cos(mAngles.y + viewRad);

    //自分の位置
    pos0 = mPos;

    //正面の位置
    pos1 = mPos;
    pos1.x += (x1 * VIEW_RANGE);
    pos1.z += (z1 * VIEW_RANGE);

    //正面から反時計回り
    pos2 = mPos;
    pos2.x += (x2 * VIEW_RANGE);
    pos2.z += (z2 * VIEW_RANGE);

    pos3 = mPos;
    pos3.x += (x3 * VIEW_RANGE);
    pos3.z += (z3 * VIEW_RANGE);

    DrawTriangle3D(pos0, pos2, pos1, 0xffffff, true);

    DrawTriangle3D(pos0, pos1, pos3, 0xffffff, true);


    DrawLine3D(pos0, pos1, 0xffffff);
    DrawLine3D(pos0, pos2, 0xffffff);
    DrawLine3D(pos0, pos3, 0xffffff);
}

void Enemy::Release(void)
{
    MV1DeleteModel(mModel);
}

void Enemy::Atack(void)
{

}

VECTOR Enemy::GetPos(void)
{
    return mPos;
}

VECTOR Enemy::GetAngle(void)
{
    return mAngles;
}
