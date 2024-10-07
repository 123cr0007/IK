#pragma once
#include "DxLib.h"
#include "appframe.h"

constexpr auto SLIDER_MAX = 100;
constexpr auto SLIDER_MIN = 0.1f;

class UI {
public:

	static UI* UIInstance;
	static UI* GetUIInstance() { return (UI*)UIInstance; }

	UI();
	~UI();
	
	void Initialize();
	void Terminate();
	void Process();
	void Draw();

	float GetSX() { return sx; }
	float GetSY() { return sy; }

private:

	int handle_slider;
	int handle_slider2;

	int hamdle_slidBer;
	int handle_slidBer2;

	float sx, sy;
};
