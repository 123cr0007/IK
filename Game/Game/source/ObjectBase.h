#pragma once
#pragma once
// ObjectBase �N���X�̒�`(Load �֐�)�� TCHAR �^��錾(�g�p)���Ă���̂ŃC���N���[�h
#include <tchar.h>
#include <unordered_map>
#include <tuple>
#include <string>

#include "DxLib.h"

// Game �N���X�ƍ��킹����
class ObjectBase {
public:
    ObjectBase();
    virtual ~ObjectBase();

    // ��������@�ƓG�̃N���X���� override ���āA���ꂼ��N���X��p�̊֐������������肷��
    virtual bool Initialize();
    virtual bool Process();
    // type=0�̎�2D��`��,type=1�̎�3D��`��,tupe = 2�̎��r���{�[�h�`��
    virtual bool Render(int type);

    virtual void End() { valid = false; }

    // �L���b�V�����Ă���n���h�����������
    virtual bool DeleteLoadType();

    // type�ɓǂݍ��݃t�@�C���ɉ������ԍ�������B0:�摜�t�@�C�� 1:MV1�t�@�C��
    int Load(const TCHAR* fileName, int type);
    virtual bool Rend(int type);


    // �Q�b�^�[
    int GetX() const { return x; }
    int GetY() const { return y; }
    VECTOR GetPos() { return vPos; };
    VECTOR GetDir() { return vDir; };
    float GetRadius() const { return collision_r; };
    bool IsValid() const { return valid; }
    int GetEffect() { return ef_type;}

    //�Z�b�^�[
    void SetPos(VECTOR pos) { vPos = pos; };

protected:
    // ��荇�����`��ɕK�v�ȍŒ���̕ϐ�
    // (DrawGraph ���K�v�Ƃ��Ă���)
    int handle;
    int ef_type;
    //�����ȂƂ���Ŏg����ėp�ϐ�
    int x;
    int y;
    int gSize;  // �r���{�[�h�`��p�̉摜�T�C�Y
    float gAngle;    // �r���{�[�h�`��p�̊p�x
    VECTOR vPos;       //
    VECTOR vDir;       //
    VECTOR capsuleTop;
    VECTOR capsuleRow;

    float collision_r;     //�L�����̔��a
    float ChHight;          //�L�����̍����i�J�v�Z�����Ƃ��́j

    
    bool valid;

    std::string fileName;
    
    static std::unordered_map<std::string, std::tuple<int>> handleCache;
};