
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"


ModeGame::ModeGame() {

	// �ϐ��̏�����
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

	// �w�i�p�n���h����ǂݍ���
	backHandle = LoadGraph("res/skysphere1.bmp");

	// �J�������`
	Cam = new Camera();
	Cam->Initialize();

	// UI���`
	ui = new UI();
	ui->Initialize();

	// �I�u�W�F�N�g��`
	mObj = new ObjectManager();
	mObj->Initialize();

	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();

	// �w�i�p�n���h�������
	DeleteGraph(backHandle);

	// �N���X�̊J��
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


	// �J�����̍X�V
	Cam->Process();

	// UI�̍X�V
	ui->Process();

	// �I�u�W�F�N�g�̍X�V
	mObj->Update();

	return true;
}

bool ModeGame::Render() {
	base::Render();

	// �w�i��`�悷��
	 DrawGraph(0, 0, backHandle, FALSE);

	// 3D��{�ݒ�
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	// �J�����̕`��
	Cam->Render();

	// UI�̕`��
	ui->Draw();

	// �I�u�W�F�N�g�̕`��
	mObj->Draw();

	return true;
}