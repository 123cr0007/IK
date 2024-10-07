#include "IK.h"


void IK::TwoBoneIK(VECTOR startPos, float arm1Length, float arm2Length, VECTOR targetPos,
    VECTOR& arm1Lot, VECTOR& arm1Lot2) {

    // memo
    /*{
        余弦定理を使う
        ボーンの長さをl1,l2,第一ルートの始点の内角をα外角をｑ1、第二ルートの始点の内角をβ外角をｑ2とすると、
        l1^2 + l2^2 - 2 * l1 * l2 * cos(θ) = x^2 + y^2となり、
        l2^2 = l1^2+ x^2 + y^2 - 2 * l1 * √(x^2 + y^2) * cos(θ)となる。
        そのため
        α = cos^-1 * (l1^2 + l2^2 - x^2 - y^2
            / 2 * l1 * l2)
        β = cos^-1 * (x^2 + y^2 + l1^2 - l2^2
            / 2 * l1 * √(x^2 + y^2))
        山折りで曲げる場合
        q1 = tan^-1 * (y/x) - β
        q2 = π -\+ α
        谷折りで曲げる場合
        q1 = tan^-1 * (y/x) - β
        q2 = π - α
    }*/

	float length = VSize(VSub(targetPos, startPos));
    if (length > (arm1Length + arm2Length)) {
		arm1Lot = VNorm(VSub(targetPos, startPos));
		arm1Lot2 = VNorm(VSub(targetPos, startPos));
        return;
    }


    // ボーンの長さの2乗
    float sqL1 = arm1Length * arm1Length;
    float sqL2 = arm2Length * arm2Length;

    // ターゲット位置
    float x = targetPos.x;
    float y = targetPos.y;
    float z = targetPos.z;  // zは今回は使わない

    // ターゲット位置の平方
    float aqX = x * x;
    float aqY = y * y;

    // 余弦定理を使って角度を計算
    float a = acosf((sqL1 + sqL2 - aqX - aqY)
        / (2.f * arm1Length * arm2Length));
    float b = acosf((aqX + aqY + sqL1 - sqL2)
        / (2.f * arm1Length * sqrtf(aqX + aqY)));

    // 山折りでの関節角度を計算
    float q1 = atan2f(y, x) - b;
    float q2 = PI - a;

    // 結果をセット
    arm1Lot = VGet(0, 0, q1);
    arm1Lot2 = VGet(0, 0, q2);
}