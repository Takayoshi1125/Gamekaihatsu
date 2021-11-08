#include<math.h>
#include"SceneManager.h"
#include"Unit.h"
#include "RollBall.h"

RollBall::RollBall(SceneManager* manager, Unit* unit)
{
    mSceneManager = manager;
    mUnit = unit;
}

void RollBall::Init(void)
{
}

void RollBall::Update(void)
{
    mStep += mSceneManager->GetDeltaTime();

    VECTOR pos = mUnit->GetPos();

    //É{Å[ÉãÇÃçÇÇ≥
    mPos.y = 50.0f;

    float dis = 50.0f;

    mPos.x =pos.x+sinf(mStep)*dis;
    mPos.z = pos.z+cosf(mStep)*dis;

}

void RollBall::Draw(void)
{
    DrawSphere3D(mPos, 20.0f, 10, 0x000000,0x000000, true);
}

void RollBall::Release(void)
{
}

VECTOR RollBall::GetPos(void)
{
    return VECTOR();
}
