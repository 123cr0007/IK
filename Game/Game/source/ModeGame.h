#pragma once

#include "appframe.h"
#include "Camera.h"
#include "ObjectManager.h"
#include <string>

// モード
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:

	ModeGame();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:



	//背景用ハンドル
	int backHandle;

    // マウスのX座標
    int mouseX;
    // マウスのY座標
    int mouseY;


    VECTOR mouseWorldStartPos;	// マウスのワールド座標(カメラの一番奥)
    VECTOR mouseWorldEndPos;	// マウスのワールド座標(カメラの一番手前)
    VECTOR oldMousePos;			// マウスのワールド座標(カプセルと円錐の中間地点)

	// カメラ
	Camera* Cam;

	// オブジェクト
	ObjectManager* mObj;
}; 
