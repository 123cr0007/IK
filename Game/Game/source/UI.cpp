#include "UI.h"

UI* UI::UIInstance = nullptr;

UI::UI() {
	UIInstance = this;

	handle_slider = -1;
	handle_slider2 = -1;
	hamdle_slidBer = -1;
	handle_slidBer2 = -1;
	sx = 2;
	sy = 2;
}

UI::~UI() {

	DeleteGraph(handle_slider);
	DeleteGraph(handle_slider2);
	DeleteGraph(hamdle_slidBer);
	DeleteGraph(handle_slidBer2);
}

void UI::Initialize() {

	
}

void UI::Terminate() {

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
}

void UI::Draw() {

	DrawSphere3D(VGet(sx, sy, 0), 1, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);

	DrawFormatString(0, 500, GetColor(0, 0, 0), "sx:%f", sx);
	DrawFormatString(0, 520, GetColor(0, 0, 0), "sy:%f", sy);
}