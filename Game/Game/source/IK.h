#pragma once
#include "DxLib.h"
#include "appframe.h"
#include <cmath>


class IK
{
public:

	// ��̃{�[����IK
	void TwoBoneIK(VECTOR startPos, float arm1Length, float arm2Length, VECTOR targetPos,
		VECTOR& arm1Lot, VECTOR& arm1Lot2);
};