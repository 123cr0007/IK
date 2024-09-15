
#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Mode//ModeServer.h"
#include"..//GamePad/GamePad.h"

// EffekseerForDXLib.h���C���N���[�h���܂��B
#include "EffekseerForDXLib.h"


class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }
	virtual int DispSizeW() { return 640; }
	virtual int DispSizeH() { return 480; }

	static	ApplicationBase* AppInstance;
	static	ApplicationBase	*GetInstance() { return AppInstance; }

	DINPUT_JOYSTATE input;		// �L�[����

	virtual int GetKey() { return _gKey; }
	virtual int GetTrg() { return _gTrg; }
	virtual DINPUT_JOYSTATE GetInput() { return input; }

protected:

	int		_gKey, _gTrg;

	ModeServer* _serverMode;

	GamePad* _gamepad;//�Q�[���p�b�h�̃A�h���X

};
