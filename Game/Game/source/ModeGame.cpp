
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"


ModeGame::ModeGame() {

	// 変数の初期化
	backHandle = -1;
	mouseX = 0;
	mouseY = 0;
	mouseWorldStartPos = VGet(0.0f, 0.0f, 0.0f);
	mouseWorldEndPos = VGet(0.0f, 0.0f, 0.0f);
	oldMousePos = VGet(0.0f, 0.0f, 0.0f);
	Cam = nullptr;
	mObj = nullptr;
	ui = nullptr;
}

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	// 背景用ハンドルを読み込む
	backHandle = LoadGraph("res/skysphere1.bmp");

	// カメラを定義
	Cam = new Camera();
	Cam->Initialize();

	// UIを定義
	ui = new UI();
	ui->Initialize();

	// オブジェクト定義
	mObj = new ObjectManager();
	mObj->Initialize();

	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();

	// 背景用ハンドルを解放
	DeleteGraph(backHandle);

	// クラスの開放
	delete Cam;
	Cam = nullptr;

	delete ui;
	ui = nullptr;

	delete mObj;
	mObj = nullptr;

	return true;
}

bool ModeGame::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();


	// カメラの更新
	Cam->Process();

	// UIの更新
	ui->Process();

	// オブジェクトの更新
	mObj->Update();

	return true;
}

bool ModeGame::Render() {
	base::Render();

	// 背景を描画する
	 DrawGraph(0, 0, backHandle, FALSE);

	// 3D基本設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	// カメラの描画
	Cam->Render();

	// UIの描画
	ui->Draw();

	// オブジェクトの描画
	mObj->Draw();

	return true;
}