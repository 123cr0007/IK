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
	moveX = 8;
}

UI::~UI() {

	DeleteGraph(handle_slider);
	DeleteGraph(handle_slider2);
	DeleteGraph(hamdle_slidBer);
	DeleteGraph(handle_slidBer2);
}

void UI::Initialize() {

	model_Joint_0 = MV1LoadModel("res/UI/Joint.mv1");
	model_Arm_0 = MV1LoadModel("res/UI/Arm.mv1");

	model_Arm_0 = MV1DuplicateModel(model_Arm_0);
	model_Joint_0 = MV1DuplicateModel(model_Joint_0);
	model_Arm_1 = MV1DuplicateModel(model_Arm_0);
	model_Joint_1 = MV1DuplicateModel(model_Joint_0);
}

void UI::Terminate() {

	MV1DeleteModel(model_Joint_0);
	MV1DeleteModel(model_Arm_0);

}

void UI::Process() {

	sx = Clamp(SLIDER_MIN, SLIDER_MAX, sx);
	sy = Clamp(SLIDER_MIN, SLIDER_MAX, sy);

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

	// 角度を計算 (sx, syに基づいてアームの方向を決定)
	float dir = atan2(sy, sx);  // atan2を使用して方向を計算
	VECTOR VDir = VGet(0, 0, dir);
	MV1SetRotationXYZ(model_Arm_0, VDir);

	// 行列計算 (スケール → 回転 → 移動の順で行列を掛け合わせる)
	MATRIX mat = MGetIdent();
	MATRIX sMat = MGetScale(VGet(0.01f, 0.01f, 0.01f));  // スケール行列
	MATRIX rMat = MGetRotZ(dir);                         // 回転行列
	MATRIX tMat = MGetTranslate(VGet(moveX, 0, 0));          // 移動行列

	// 順序に従って行列を掛け合わせる
	mat = MMult(mat, sMat);  // スケールをまず適用
	mat = MMult(mat, tMat);  // 最後に移動
	mat = MMult(mat, rMat);  // 次に回転

	// モデルに行列を適用
	MV1SetMatrix(model_Arm_1, mat);
	MV1SetMatrix(model_Joint_1, mat);
}

void UI::Draw() {

	VECTOR scale = VGet(0.01f, 0.01f, 0.01f);
	MV1SetScale(model_Arm_0, scale);
	MV1SetScale(model_Joint_0, scale);

	DrawSphere3D(VGet(sx, sy, 0), 1, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);

	MV1DrawModel(model_Joint_0);
	MV1DrawModel(model_Arm_0);
	MV1DrawModel(model_Joint_1);
	MV1DrawModel(model_Arm_1);

	DrawFormatString(0, 500, GetColor(0, 0, 0), "sx:%f", sx);
	DrawFormatString(0, 520, GetColor(0, 0, 0), "sy:%f", sy);
	DrawFormatString(0, 540, GetColor(0, 0, 0), "mx:%f", moveX);


	VECTOR pos1 = MV1GetPosition(model_Arm_0);
	VECTOR pos2 = MV1GetPosition(model_Arm_1);
}