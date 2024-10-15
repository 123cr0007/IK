#pragma once
#include "DxLib.h"
#include "appframe.h"
#include "IK.h"

constexpr auto SLIDER_MAX = 20;
constexpr auto SLIDER_MIN = 0.1f;

constexpr auto ARM_SCALE = 0.01f;

class UI {
public:

	static UI* UIInstance;
	static UI* GetUIInstance() { return (UI*)UIInstance; }

	UI();
	virtual ~UI();
	
	void Initialize();
	void Process();
	void Draw();

	float GetSX() { return sx; }
	float GetSY() { return sy; }

private:

	int handle_slider;
	int handle_slider2;

	int hamdle_slidBer;
	int handle_slidBer2;

	int model_Joint_0;
	int model_Joint_1;
	int model_Arm_0;
	int model_Arm_1;

	int model_Arms;

	float sx, sy;
	float armLength;

	IK* ik;
};