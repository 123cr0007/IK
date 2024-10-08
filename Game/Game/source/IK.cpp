#include "IK.h"


void IK::TwoBoneIK(VECTOR startPos, float arm1Length, float arm2Length, VECTOR targetPos,
    float& arm1Lot, float& arm1Lot2) {

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

    // ターゲットとの距離
    float length = VSize(VSub(targetPos, startPos));

    // 腕がターゲットに届かない場合
    if (length > (arm1Length + arm2Length)) {
        // 腕をターゲット方向に一直線に伸ばす
        arm1Lot = atan2f(targetPos.y - startPos.y, targetPos.x - startPos.x);
        arm1Lot2 = 0.0f; // 腕2はまっすぐに伸びる
        return;
    }

    // ボーンの長さの2乗
    float sqL1 = arm1Length * arm1Length;
    float sqL2 = arm2Length * arm2Length;

    // ターゲット位置の平方
    float x = targetPos.x - startPos.x;
    float y = targetPos.y - startPos.y;
    float aqX = x * x;
    float aqY = y * y;

    // 余弦定理を使って角度を計算
    float a = acosf(Clamp(-1.0f, 1.0f ,
        (sqL1 + sqL2 - aqX + aqY)
        / (2.f * arm1Length * arm2Length)));
    float b = acosf(Clamp(-1.0f, 1.0f, 
        (aqX + aqY + sqL1 - sqL2)
        / (2.f * arm1Length * length)));

    // 関節角度の計算
    float q1 = atan2f(y, x) - b;    // 腕1の角度
    float q2 = PI - a;              // 腕2の角度

    // 結果をセット
    arm1Lot = q1;
    arm1Lot2 = q2;
}