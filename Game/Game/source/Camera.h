#pragma once
#include "DxLib.h"
#include "ApplicationMain.h"

//�f�t�H���g�̃v���C���[�ƃJ�����̋���
const auto DEFAULT_DIST = 1500.0f;

//�@�X�^�[�g�̃v���C���[�ƃJ�����̋���
const auto START_DIST = 25.0f;

//�L�����𓧖��������n�߂�p�x�Ɗ��S�ɓ����ɂȂ�p�x
//XZ���ʂɕ��s�̎���0�Ƃ��āA��������ǂꂾ�������邩
const auto OPACITY_START = 20;
const auto OPACITY_END = 60;


class Camera {
public:

	static Camera* CamInstance;
	static Camera* GetCamInstance() { return (Camera*)CamInstance; }

	Camera();
	virtual ~Camera();

	static Camera* Instance;
	static Camera* GetInstance() { return (Camera*)Instance; }

	bool Initialize();
	bool Process();
	bool Render();

	//�Q�b�^�[
	VECTOR GetCamPos() { return _vPos; };
	VECTOR GetTgtPos() { return _vTarget; };
	float  GetRadH() { return radH; };
	float  GetRadY() { return radY; };
	float  GetClipFar() { return _clipFar; };

	//�Z�b�^�[
	void SetCamPos(VECTOR pos) { _vPos = pos; };
	void SetTgtPos(VECTOR pos) { _vTarget = pos; };

protected:
	VECTOR	_vPos;					// �ʒu
	VECTOR	_vTarget;				// ����
	float	_vDirection;			// �p�x
	float	_clipNear, _clipFar;	// �N���b�v

	VECTOR	_vOldPos;					// �ʒu
	VECTOR	_vOldTarget;				// ����

	//�ォ�猩������X�����牽�x����Ă邩�i���xY�����񂵂����j
	float radY;
	//�����猩������Y=0���牽�x�オ���Ă��邩
	float radH;
	//�v���C���[�ƃJ�����̋���
	float CamDist;
	float ChengeDist;
	bool OldCheck;

	//�L�����̓����x�Z�b�g�p
	float opacityRate;
};