#pragma once
#include "DxLib.h"
#include <string>
#include <vector>
#include "stdlib.h"

//�p123���݊p�����ׂ�
float CheckAngle(VECTOR p1, VECTOR p2, VECTOR p3);

// ���s�֌W�����ׂ�
// 0�������畽�s
bool isParallel(VECTOR p1, VECTOR p2);

void clamp01(float& v);
void clanp1m1(float& v);


//�_�ƒ����̍ŒZ����
//�_p1�ƒ���p2a,p2b�̍ŒZ���������߂�
float CheckDistPointLine(VECTOR p1, VECTOR p2a, VECTOR p2b, VECTOR* h, float* t);

//�_�Ɛ����̍ŒZ����
//�_p1�Ɛ���p2a,p2b�̍ŒZ���������߂�
float CheckDistPointSegment(VECTOR p1, VECTOR p2a, VECTOR p2b, VECTOR* h, float* t);

//�����̒����̍ŒZ����
//����p1a,p1b�ƒ���p2a,p2b�̍ŒZ���������߂�
//h1,h2�͂��ꂼ�꒼��p1a,p1b�ƒ���p2a,p2b�̍ŒZ�����̌�_
float CheckDistLineLine(VECTOR p1a, VECTOR p1b, VECTOR p2a, VECTOR p2b, VECTOR* h1, VECTOR* h2, float* t1, float* t2);

//�������m�̍ŒZ����
//����p1a,p1b�Ɛ���p2a,p2b�̍ŒZ���������߂�
//h1,h2�͂��ꂼ�����p1a,p1b�Ɛ���p2a,p2b�̍ŒZ�����̌�_
float CheckDistSegment(VECTOR p1a, VECTOR p1b, VECTOR p2a, VECTOR p2b, VECTOR* h1, VECTOR* h2, float* t1, float* t2);

//�J�v�Z�����m���������Ă邩�ǂ���
bool CheckHitCapsule(VECTOR p1a, VECTOR p1b, VECTOR p2a, VECTOR p2b, float t1, float t2);

//�_�ƃJ�v�Z��
bool CheckHitPointCapsule(VECTOR p1a, VECTOR p1b, VECTOR p2, float t1, float t2);

//�J�v�Z�����m�̉����߂�����
VECTOR CheckCapsule(VECTOR p1a, VECTOR p1b, float r1, VECTOR p2a, VECTOR p2b, float r2);

//�ǎC��x�N�g���̍쐬
VECTOR MakeWallLap(MV1_COLL_RESULT_POLY HitNorm, VECTOR MoveV);

//abs�֐����g���ăx�N�g���̐�Βl�����߂�
float VectorAbs(VECTOR v);

//�_�Ɖ~���̓����蔻��
bool CheckHitPointCorn(VECTOR top,VECTOR bottom,float r,VECTOR p);

// �����ƕ��ʂ̌�������
// �_p1a�Ɩ@��p1n�̕��ʂƐ���p2a,p2b�̌�������
// h�͌�_
bool CheckHitSegmentPlane(VECTOR p1a, VECTOR p1n, VECTOR p2a, VECTOR p2b, VECTOR& h);

// �����ƕ��ʂ̌�������
// �_p1a,p1b,p1c�̕��ʂƐ���p2a,p2b�̌�������
// h�͌�_
bool CheckHitTriangleSegment(VECTOR p1a, VECTOR p1b, VECTOR p1c, VECTOR p2a, VECTOR p2b, VECTOR& h, float& t);