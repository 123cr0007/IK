#pragma once
#include "DxLib.h"
#include "appframe.h"
#include <cmath>


class IK
{
public:

	// 二つのボーンのIK
	void TwoBoneIK(VECTOR startPos, float arm1Length, float arm2Length, VECTOR targetPos,
		float& arm1Lot, float& arm1Lot2);
};