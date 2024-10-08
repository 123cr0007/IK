#include "IK.h"


void IK::TwoBoneIK(VECTOR startPos, float arm1Length, float arm2Length, VECTOR targetPos,
    float& arm1Lot, float& arm1Lot2) {

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

    // �^�[�Q�b�g�Ƃ̋���
    float length = VSize(VSub(targetPos, startPos));

    // �r���^�[�Q�b�g�ɓ͂��Ȃ��ꍇ
    if (length > (arm1Length + arm2Length)) {
        // �r���^�[�Q�b�g�����Ɉ꒼���ɐL�΂�
        arm1Lot = atan2f(targetPos.y - startPos.y, targetPos.x - startPos.x);
        arm1Lot2 = 0.0f; // �r2�͂܂������ɐL�т�
        return;
    }

    // �{�[���̒�����2��
    float sqL1 = arm1Length * arm1Length;
    float sqL2 = arm2Length * arm2Length;

    // �^�[�Q�b�g�ʒu�̕���
    float x = targetPos.x - startPos.x;
    float y = targetPos.y - startPos.y;
    float aqX = x * x;
    float aqY = y * y;

    // �]���藝���g���Ċp�x���v�Z
    float a = acosf(Clamp(-1.0f, 1.0f ,
        (sqL1 + sqL2 - aqX + aqY)
        / (2.f * arm1Length * arm2Length)));
    float b = acosf(Clamp(-1.0f, 1.0f, 
        (aqX + aqY + sqL1 - sqL2)
        / (2.f * arm1Length * length)));

    // �֐ߊp�x�̌v�Z
    float q1 = atan2f(y, x) - b;    // �r1�̊p�x
    float q2 = PI - a;              // �r2�̊p�x

    // ���ʂ��Z�b�g
    arm1Lot = q1;
    arm1Lot2 = q2;
}