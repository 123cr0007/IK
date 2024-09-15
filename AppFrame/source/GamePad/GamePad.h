#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "Dxlib.h"

constexpr int MULTIPAD_MAX = 10;	// �ő�ŁA�p�b�h9�{�L�[�{�[�h��10��

constexpr int PLAYER_0 = 0; //�L�[�{�[�h
constexpr int PLAYER_1 = 1;	//�v���C���[�P

class GamePad {

public:

	GamePad();			// �R���X�g���N�^
	virtual ~GamePad();	// �f�X�g���N�^

	void Input();		// ���͍X�V

	//����
	static GamePad* Instance;
	static GamePad* GetInstance() { return Instance; }

	// �����Q�[���p�b�h�p�̏ꍇ
	struct MULTIPAD {
		int key;			// �L�[���͂̏��
		int trg;			// �g���K���͂̏��
		int rel;			// �����[�X���͂̏��
		float LX;		//���X�e�B�b�N��X�����
		float LY;		//���X�e�B�b�N��Y�����
		float RX;		//�E�X�e�B�b�N��X�����
		float RY;		//�E�X�e�B�b�N��Y�����
	};

	MULTIPAD GetMultiPad(int pl_num) {return pad[pl_num];};
	int GetKey(int pl_num) { return pad[pl_num].key; }
	int GetTrg(int pl_num) { return pad[pl_num].trg; }
	int GetLX(int pl_num) { return pad[pl_num].LX; }
	int GetLY(int pl_num) { return pad[pl_num].LY; }
	int GetRX(int pl_num) { return pad[pl_num].RX; }
	int GetRY(int pl_num) { return pad[pl_num].RY; }
	int GetGamePadNum() { return GamePadNum; };

protected:

	// �L�[�{�[�h���Q�[���p�b�h1�̂ǂ���ł��g����ꍇ
	int key;			// �L�[���͂̏��
	int trg;			// �g���K���͂̏��
	int rel;			// �����[�X���͂̏��

	//�Q�[���p�b�h�̐ڑ����Ǘ��p
	int GamePadNum;

	MULTIPAD	pad[MULTIPAD_MAX];


	//Xbox360�R���g���[���[�̐��f�[�^
	XINPUT_STATE xinput;

	//�_�C���N�g�C���v�b�g�R���g���[���[�̐��f�[�^
	DINPUT_JOYSTATE dinput;
};

