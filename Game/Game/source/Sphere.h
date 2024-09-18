#pragma once

#include "appframe.h"
#include "ObjectBase.h"
#include <string>


class Sphere : public ObjectBase {
public:

    // �C���X�^���X�̐���
    static Sphere* SpherelInstance;
    static Sphere* GetSphereInstance() { return (Sphere*)SpherelInstance; }

    Sphere();

    bool Initialize()override;
    bool Terminate();
    bool Process()override;
    bool Render(int type) override;

    // �t���[���̔ԍ�����������
    void GetFrameInfoFromIndex(int chHandle, int index);
    // �t���[���̖��O����������
    void GetFrameInfoFromName(int chHandle, const CHAR* name);

protected:

    // 3D���f���`��p
    int ModelHandle;

    struct SphereInfo {
        VECTOR position;   // �ʒu
        MATRIX localMat;   // ��]�s��
        float radius;      // ���a
        int color = GetColor(0, 0, 0);// �F
        int index;         // ���̔ԍ�
        bool isHit = false; // �����蔻��t���O
    };
    // ���̂̔z��
    std::vector<SphereInfo> spheres;

    // ���̂̏������֐�
    void initializeSpheres();
    // ���̂̓����蔻��֐�
    void hitCheckSpheres();


    // �}�E�X��X���W
    int mouseX;
    // �}�E�X��Y���W
    int mouseY;

    // ���̋���
    float sLengh;


    // �L�����N�^�[�n���h��
	int charHandle;

    // �}�E�X�Ƌ��̋���
    float mouseSphereLengh;
    float oldMouseSphereLengh;

    VECTOR mouseWorldStartPos;	// �}�E�X�̃��[���h���W(�J�����̈�ԉ�)
    VECTOR mouseWorldEndPos;	// �}�E�X�̃��[���h���W(�J�����̈�Ԏ�O)
    VECTOR oldMousePos;			// �}�E�X�̃��[���h���W(�J�v�Z���Ɖ~���̒��Ԓn�_)
    VECTOR mouseLine;			// �}�E�X�̃��[���h���W(�J�����̈�ԉ������Ԏ�O�܂ł̒���)

    // �f�o�b�O�p
    VECTOR debugPos;
    VECTOR debugPos2;
    VECTOR debugPos3;

    float checkLengh;
    float checkLengh2;
};