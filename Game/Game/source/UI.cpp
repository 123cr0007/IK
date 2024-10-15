#include "UI.h"

UI* UI::UIInstance = nullptr;

UI::UI() {
	UIInstance = this;

	handle_slider = -1;
	handle_slider2 = -1;
	hamdle_slidBer = -1;
	handle_slidBer2 = -1;

	model_Joint_0 = -1;
	model_Joint_1 = -1;
	model_Arm_0 = -1;
	model_Arm_1 = -1;

	sx = 2;
	sy = 2;

	ik = new IK();
}

UI::~UI() {

	MV1DeleteModel(handle_slider);
	MV1DeleteModel(handle_slider2);
	MV1DeleteModel(hamdle_slidBer);
	MV1DeleteModel(handle_slidBer2);
	MV1DeleteModel(model_Arm_0);
	MV1DeleteModel(model_Arm_1);
	MV1DeleteModel(model_Joint_0);
	MV1DeleteModel(model_Joint_1);
	MV1DeleteModel(model_Arms);
}

void UI::Initialize() {

	model_Joint_0 = MV1LoadModel("res/UI/Joint.mv1");
	model_Arm_0 = MV1LoadModel("res/UI/Arm.mv1");
	model_Arms = MV1LoadModel("res/Lynette/Lynette.mv1");

	model_Arm_0 = MV1DuplicateModel(model_Arm_0);
	model_Joint_0 = MV1DuplicateModel(model_Joint_0);
	model_Arm_1 = MV1DuplicateModel(model_Arm_0);
	model_Joint_1 = MV1DuplicateModel(model_Joint_0);

	int arm1BoneIndex = MV1SearchFrame(model_Arms, "���r");
	VECTOR pos = MV1GetFramePosition(model_Arms, arm1BoneIndex);
	sx = pos.x + 2;
	sy = pos.y + 2;
}

void UI::Process() {

	// ���E�{�^����sx��ύX
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		if (sx >= SLIDER_MIN) {
			sx -= 0.05f;
		}
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if (sx <= SLIDER_MAX) {
			sx += 0.05f;
		}
	}

	// �㉺�{�^����sy��ύX
	if (CheckHitKey(KEY_INPUT_UP)) {
		if (sx <= SLIDER_MAX) {
			sy += 0.05f;
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		if (sx >= SLIDER_MIN) {
			sy -= 0.05f;
		}
	}

	sx = Clamp(SLIDER_MIN, SLIDER_MAX, sx);
	sy = Clamp(SLIDER_MIN, SLIDER_MAX, sy);

	// ���f���̃{�[���̃C���f�b�N�X������
	int arm1BoneIndex = MV1SearchFrame(model_Arms, "���r");
	int arm2BoneIndex = MV1SearchFrame(model_Arms, "���Ђ�");
	int endArmBoneIndex = MV1SearchFrame(model_Arms, "�����");

	// ���[�J�����W���擾
	MATRIX arm1LocalMat = MV1GetFrameLocalMatrix(model_Arms, arm1BoneIndex);
	MATRIX arm2LocalMat = MV1GetFrameLocalMatrix(model_Arms, arm2BoneIndex);
	MATRIX endArmLocalMat = MV1GetFrameLocalMatrix(model_Arms, endArmBoneIndex);

	// ���[���h���W���擾
	VECTOR arm1WorldPos = MV1GetFramePosition(model_Arms, arm1BoneIndex);
	VECTOR arm2WorldPos = MV1GetFramePosition(model_Arms, arm2BoneIndex);
	VECTOR endArmWorldPos = MV1GetFramePosition(model_Arms, endArmBoneIndex);

	// ���[�J���ł�X���̊g��l��r�̒����Ƃ���
	float arm1Length = VSize(VSub(arm2WorldPos, arm1WorldPos));
	float arm2Length = VSize(VSub(endArmWorldPos, arm2WorldPos));

	// �p�x�ۑ�����悤
	float arm1Lot = 0.0f;
	float arm2Lot = 0.0f;

	ik->TwoBoneIK(arm1WorldPos, arm1Length, arm2Length,
		VGet(sx, sy, 0), arm1Lot, arm2Lot);

	// �s��v�Z (�X�P�[�� �� �ړ� �� ��]�̏��ōs����|�����킹��)
	MATRIX arm1Mat = MGetIdent();
	MATRIX arm2Mat = MGetIdent();
	// ��]�s��
	MATRIX arm1RMat = MGetRotZ(arm1Lot);
	MATRIX arm2RMat = MGetRotZ(arm2Lot);

	arm1Mat = MMult(arm1Mat, arm1RMat);
	arm2Mat = MMult(arm2Mat, arm2RMat);

	// ���f���ɍs���K�p
	MV1SetFrameUserLocalMatrix(model_Arms, arm1BoneIndex, arm1Mat);
	MV1SetFrameUserLocalMatrix(model_Arms, arm2BoneIndex, arm2Mat);

	armLength = arm1Length;
}

void UI::Draw() {

	//DrawSphere3D(VGet(sx, sy, 0), 1, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);

#if 0
	MV1DrawModel(model_Joint_0);
	MV1DrawModel(model_Arm_0);
	MV1DrawModel(model_Joint_1);
	MV1DrawModel(model_Arm_1);
#else
	MV1DrawModel(model_Arms);
#endif


	DrawFormatString(0, 500, GetColor(0, 0, 0), "sx:%f", sx);
	DrawFormatString(0, 520, GetColor(0, 0, 0), "sy:%f", sy);
	DrawFormatString(0, 540, GetColor(0, 0, 0), "armLength:%f", armLength);


	VECTOR pos1 = MV1GetPosition(model_Arm_0);
	VECTOR pos2 = MV1GetPosition(model_Arm_1);
}