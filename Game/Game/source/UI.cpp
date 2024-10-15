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

}

void UI::Initialize() {

	model_Arms = MV1LoadModel("res/Lynette/Lynette.mv1");

	int arm1BoneIndex = MV1SearchFrame(model_Arms, "左腕");
	VECTOR pos = MV1GetFramePosition(model_Arms, arm1BoneIndex);
	sx = pos.x + 2;
	sy = pos.y + 2;

	MV1DeleteModel(model_Arms);
	model_Arms = -1;
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
}

void UI::Draw() {

	DrawSphere3D(VGet(sx, sy, 0), 1, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
	DrawFormatString(0, 500, GetColor(0, 0, 0), "sx:%f", sx);
	DrawFormatString(0, 520, GetColor(0, 0, 0), "sy:%f", sy);
	DrawFormatString(0, 540, GetColor(0, 0, 0), "armLength:%f", armLength);


	VECTOR pos1 = MV1GetPosition(model_Arm_0);
	VECTOR pos2 = MV1GetPosition(model_Arm_1);
}