
#include "ApplicationBase.h"

ApplicationBase	*ApplicationBase::AppInstance = NULL;


ApplicationBase::ApplicationBase() {
	AppInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// DX���C�u�����̏�����
	if(AppWindowed()){
		ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);

	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	SetZBufferBitDepth(32);

	// 3DSound: XAudio���g�p
	SetEnableXAudioFlag(TRUE);			// �L���ɂ���ƃp���⃊�o�[�u���L���ɂȂ�

	// 3DSound:�P���[�g���ɑ�������l��ݒ肷��
	Set3DSoundOneMetre(1.0f);

	if (DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g

	

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// ����������
	srand((unsigned int)time(NULL));

	//�R���g���[���[�̏�����
	_gamepad = new GamePad();

	// ���[�h�T�[�o�̏�����
	_serverMode = new ModeServer();

	return true;
}

bool ApplicationBase::Terminate() {
	// Effekseer���I������B
	Effkseer_End();

	// DX���C�u�����J��
	DxLib_End();

	return true;
}


bool ApplicationBase::Input() {
	// �Q�[���p�b�h����
	   
	  _gamepad->Input();
	// �L�[�̓��́A�g���K���͂𓾂�
	int keyold = _gKey;
	_gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	GetJoypadDirectInputState(DX_INPUT_KEY_PAD1, &input);
	_gTrg = (_gKey ^ keyold) & _gKey;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j

	return true;
}

bool ApplicationBase::Process() {
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();
	return true;
}

bool ApplicationBase::Render() {
	_serverMode->RenderInit();
	_serverMode->Render();
	_serverMode->RenderFinish();
	return true;
}
