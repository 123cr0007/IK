#include "IK.h"


void IK::TwoBoneIK(VECTOR startPos, float arm1Length, float arm2Length, VECTOR targetPos,
    VECTOR& arm1Lot, VECTOR& arm1Lot2) {

    // memo
    /*{
        �]���藝���g��
        �{�[���̒�����l1,l2,��ꃋ�[�g�̎n�_�̓��p�����O�p����1�A��񃋁[�g�̎n�_�̓��p�����O�p����2�Ƃ���ƁA
        l1^2 + l2^2 - 2 * l1 * l2 * cos(��) = x^2 + y^2�ƂȂ�A
        l2^2 = l1^2+ x^2 + y^2 - 2 * l1 * ��(x^2 + y^2) * cos(��)�ƂȂ�B
        ���̂���
        �� = cos^-1 * (l1^2 + l2^2 - x^2 - y^2
            / 2 * l1 * l2)
        �� = cos^-1 * (x^2 + y^2 + l1^2 - l2^2
            / 2 * l1 * ��(x^2 + y^2))
        �R�܂�ŋȂ���ꍇ
        q1 = tan^-1 * (y/x) - ��
        q2 = �� -\+ ��
        �J�܂�ŋȂ���ꍇ
        q1 = tan^-1 * (y/x) - ��
        q2 = �� - ��
    }*/

	float length = VSize(VSub(targetPos, startPos));
    if (length > (arm1Length + arm2Length)) {
		arm1Lot = VNorm(VSub(targetPos, startPos));
		arm1Lot2 = VNorm(VSub(targetPos, startPos));
        return;
    }


    // �{�[���̒�����2��
    float sqL1 = arm1Length * arm1Length;
    float sqL2 = arm2Length * arm2Length;

    // �^�[�Q�b�g�ʒu
    float x = targetPos.x;
    float y = targetPos.y;
    float z = targetPos.z;  // z�͍���͎g��Ȃ�

    // �^�[�Q�b�g�ʒu�̕���
    float aqX = x * x;
    float aqY = y * y;

    // �]���藝���g���Ċp�x���v�Z
    float a = acosf((sqL1 + sqL2 - aqX - aqY)
        / (2.f * arm1Length * arm2Length));
    float b = acosf((aqX + aqY + sqL1 - sqL2)
        / (2.f * arm1Length * sqrtf(aqX + aqY)));

    // �R�܂�ł̊֐ߊp�x���v�Z
    float q1 = atan2f(y, x) - b;
    float q2 = PI - a;

    // ���ʂ��Z�b�g
    arm1Lot = VGet(0, 0, q1);
    arm1Lot2 = VGet(0, 0, q2);
}