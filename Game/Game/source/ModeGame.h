#pragma once

#include "appframe.h"
#include "Camera.h"
#include "ObjectManager.h"
#include <string>

// ���[�h
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



	//�w�i�p�n���h��
	int backHandle;

    // �}�E�X��X���W
    int mouseX;
    // �}�E�X��Y���W
    int mouseY;


    VECTOR mouseWorldStartPos;	// �}�E�X�̃��[���h���W(�J�����̈�ԉ�)
    VECTOR mouseWorldEndPos;	// �}�E�X�̃��[���h���W(�J�����̈�Ԏ�O)
    VECTOR oldMousePos;			// �}�E�X�̃��[���h���W(�J�v�Z���Ɖ~���̒��Ԓn�_)

	// �J����
	Camera* Cam;

	// �I�u�W�F�N�g
	ObjectManager* mObj;
}; 
