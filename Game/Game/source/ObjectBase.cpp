// DX ���C�u�����̋@�\(LoadGraph / DrawGraph)���g�p���Ă���̂ŃC���N���[�h
#include "DxLib.h"
#include "ObjectBase.h"

// static �ȃ����o�ϐ��͕ʓr���[�J���ɐ錾����K�v������
std::unordered_map<std::string, std::tuple<int>> ObjectBase::handleCache;

ObjectBase::ObjectBase() {
    
    x = 0;
    y = 0;
    vPos = VGet(0, 0, 0);
    vDir = VGet(0, 0, 0);
    capsuleTop = VGet(0, 0, 0);
    collision_r = 0.f;
    ChHight = 0.f;
    handle = -1;
    valid = false;
}

ObjectBase::~ObjectBase() {
}

bool ObjectBase::DeleteLoadType() {

    if (fileName.empty()) {
        return false;
    }

    auto cache = handleCache[fileName];
    auto handle = std::get<0>(cache);

    if (handle == -1) {
        return false;
    }

    // ���� LoadGraph �����摜�� DeleteGraph �Ŕj�����Ȃ��ƃr�f�I���������������Ă��܂�
    DeleteGraph(handle);

    handleCache[this->fileName] = std::make_tuple(-1);
    fileName.clear();

    return true;
}

// ���@���G���摜�̓ǂݍ��݂͂���͂��Ȃ̂ŋ��ʂ̏����Ƃ��Ď���
// ���@���G�̃N���X��h���N���X�ɂ��Ă��A���� Load �����ʂŎg���Ηǂ��݌v
// type=0�̎�2D�����[�h,type=1�̎�3D�����[�h
int ObjectBase::Load(const TCHAR* fileName, int type) {

    if (this->fileName.empty()) {
        this->fileName = std::string(fileName);
    }

    if (handleCache.count(this->fileName) == 0) {
        int n = 0;
        switch (type) {
        case 0:

            handle = LoadGraph(fileName);
            GetGraphSize(handle, &gSize, &n);
            break;
        case 1:

            handle = MV1LoadModel(fileName);
            break;
        }
        

        if (handle != -1) {

            handleCache[this->fileName] = std::make_tuple(handle);
        }
    }
    else {
        auto cache = handleCache[this->fileName];

        handle = std::get<0>(cache);
    }

    return handle;
}

bool ObjectBase::Initialize() {

    capsuleTop = VGet(vPos.x, vPos.y + ChHight, vPos.z);
    return true;
}


bool ObjectBase::Process() {
    return true;
}

bool ObjectBase::Render(int type) {

    Rend(type);
    return true;
}


bool ObjectBase::Rend(int type) {
 
    switch (type) {
    case 0:
        DrawGraph(x, y, handle, TRUE);
        break;

    case 1:
        MV1DrawModel(handle);
        break;

    case 2:
        DrawBillboard3D(vPos, 1.0f, 0.5f, gSize, gAngle, handle, TRUE);
    }
    return true;
}