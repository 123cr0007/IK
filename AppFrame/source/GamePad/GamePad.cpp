#include "Dxlib.h"
#include "GamePad.h"

GamePad *GamePad::Instance = NULL;

GamePad::GamePad() {

	Instance = this;
	key = 0;
	trg = 0;
	rel = 0;

	// �����Q�[���p�b�h�p
	for(int i = 0; i < MULTIPAD_MAX; i++) {
		pad[i].key = 0;
		pad[i].trg = 0;
		pad[i].rel = 0;
		pad[i].LX = 0;
		pad[i].LY = 0;
		pad[i].RX = 0;
		pad[i].RY = 0;
	}

	//�ڑ�����Ă����R���g���[���[����ۊ�
	GamePadNum = GetJoypadNum();

	xinput = { 0 };

	dinput = { 0 };

}

GamePad::~GamePad() {
	
}

void GamePad::Input() {
	//// �L�[���́A�g���K���́A�����[�X���͂𓾂�
	//int keyold = key;
	//
	//key =  GetJoypadInputState(DX_INPUT_PAD1);		// �L�[���͂��擾
	//trg = (key ^ keyold) & key;
	//rel = (key ^ keyold) & ~key;

	// �����Q�[���p�b�h�p
	int padTbl[] = {
		DX_INPUT_KEY,	// 0:�L�[����
		DX_INPUT_PAD1,	// 1:�p�b�h1
		DX_INPUT_PAD2,	// 2:�p�b�h2
		DX_INPUT_PAD3,	// 3:�p�b�h3
		DX_INPUT_PAD4,	// 4:�p�b�h4
		DX_INPUT_PAD5,	// 5:�p�b�h5
		DX_INPUT_PAD6,	// 6:�p�b�h6
		DX_INPUT_PAD7,	// 7:�p�b�h7
		DX_INPUT_PAD8,	// 8:�p�b�h8
		DX_INPUT_PAD9,	// 9:�p�b�h9

	};

	//�Q�[���p�b�h���ڑ�����Ă���Ȃ�
	if (GamePadNum > 0 ) {

		//����

		//�Q�[���p�b�h�̐ڑ�������������Ȃ�
		if(GamePadNum < MULTIPAD_MAX){

			//����

			for (int i = 0; i < MULTIPAD_MAX; i++)
			{
				if (CheckJoypadXInput(padTbl[i])) {

					int keyold = pad[i].key;
					pad[i].key = GetJoypadInputState(padTbl[i]);
					pad[i].trg = (pad[i].key ^ keyold) & pad[i].key;
					pad[i].rel = (pad[i].key ^ keyold) & ~pad[i].key;

					GetJoypadXInputState(padTbl[i], &xinput);
					pad[i].LX = xinput.ThumbLX;
					pad[i].LY = -xinput.ThumbLY;
					pad[i].RX = xinput.ThumbRX;
					pad[i].RY = -xinput.ThumbRY;

				}
				else
				{
					int keyold = pad[i].key;
					pad[i].key = GetJoypadInputState(padTbl[i]);
					GetJoypadDirectInputState(padTbl[i], &dinput);
					pad[i].trg = (pad[i].key ^ keyold) & pad[i].key;
					pad[i].rel = (pad[i].key ^ keyold) & ~pad[i].key;
					pad[i].LX = dinput.X;
					pad[i].LY = dinput.Y;

				}

			}
		}
	}
}


