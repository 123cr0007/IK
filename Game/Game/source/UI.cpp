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

	int arm1BoneIndex = MV1SearchFrame(model_Arms, "左腕");
	VECTOR pos = MV1GetFramePosition(model_Arms, arm1BoneIndex);
	sx = pos.x + 2;
	sy = pos.y + 2;
}

void UI::Process() {

	// 左右ボタンでsxを変更
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

	// 上下ボタンでsyを変更
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

	// モデルのボーンのインデックスをえる
	int arm1BoneIndex = MV1SearchFrame(model_Arms, "左腕");
	int arm2BoneIndex = MV1SearchFrame(model_Arms, "左ひじ");
	int endArmBoneIndex = MV1SearchFrame(model_Arms, "左手首");

	// ローカル座標を取得
	MATRIX arm1LocalMat = MV1GetFrameLocalMatrix(model_Arms, arm1BoneIndex);
	MATRIX arm2LocalMat = MV1GetFrameLocalMatrix(model_Arms, arm2BoneIndex);
	MATRIX endArmLocalMat = MV1GetFrameLocalMatrix(model_Arms, endArmBoneIndex);

	// ワールド座標を取得
	VECTOR arm1WorldPos = MV1GetFramePosition(model_Arms, arm1BoneIndex);
	VECTOR arm2WorldPos = MV1GetFramePosition(model_Arms, arm2BoneIndex);
	VECTOR endArmWorldPos = MV1GetFramePosition(model_Arms, endArmBoneIndex);

	// ローカルでのX軸の拡大値を腕の長さとする
	float arm1Length = VSize(VSub(arm2WorldPos, arm1WorldPos));
	float arm2Length = VSize(VSub(endArmWorldPos, arm2WorldPos));

	// 角度保存するよう
	float arm1Lot = 0.0f;
	float arm2Lot = 0.0f;

	ik->TwoBoneIK(arm1WorldPos, arm1Length, arm2Length,
		VGet(sx, sy, 0), arm1Lot, arm2Lot);

	// 行列計算 (スケール → 移動 → 回転の順で行列を掛け合わせる)
	MATRIX arm1Mat = MGetIdent();
	MATRIX arm2Mat = MGetIdent();
	// 回転行列
	MATRIX arm1RMat = MGetRotZ(arm1Lot);
	MATRIX arm2RMat = MGetRotZ(arm2Lot);

	arm1Mat = MMult(arm1Mat, arm1RMat);
	arm2Mat = MMult(arm2Mat, arm2RMat);

	// モデルに行列を適用
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