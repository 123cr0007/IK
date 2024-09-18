#include "Sphere.h"
#include "Player.h"

// �C���X�^���X�̐���
Sphere* Sphere::SpherelInstance = nullptr;
Sphere::Sphere() {

}

bool Sphere::Initialize() {
	
	// �n���h��
	charHandle = -1;
	if (Player::GetPlInstance() != nullptr) {
		charHandle = Player::GetPlInstance()->GetHandle();
	}

	GetFrameInfoFromName(charHandle, "���r");	// ��
	GetFrameInfoFromName(charHandle, "���Ђ�");	// ��
	GetFrameInfoFromName(charHandle, "�����");	// ��

	return true;
}

bool Sphere::Terminate() {
	

	return true;
}

bool Sphere::Process() {

	return true;
}

bool Sphere::Render(int type) {

	// ���̂̕`��
	for (auto& s : spheres) {
		DrawSphere3D(s.position, s.radius, 8, s.color, s.color, TRUE);
	}

	return true;
}

void Sphere::GetFrameInfoFromIndex(int chHandle, int index) {

	// ���̏��
	SphereInfo sInfo;

	// �t���[���̏����擾
	sInfo.localMat = MV1GetFrameLocalMatrix(chHandle, index);
	sInfo.position = MV1GetFramePosition(chHandle, index);
	sInfo.index = index;
	sInfo.radius = 0.5f;

	spheres.push_back(sInfo);

}


void Sphere::GetFrameInfoFromName(int chHandle, const CHAR* name) {

	// ���̏��
	SphereInfo sInfo;

	// �t���[���̖��O����������
	int index = MV1SearchFrame(chHandle, name);
	if (index == -1) {
		return;
	}

	// �t���[���̏����擾
	sInfo.localMat = MV1GetFrameLocalMatrix(chHandle, index);
	sInfo.position = MV1GetFramePosition(chHandle, index);
	sInfo.index = index;
	sInfo.radius = 0.5f;

	spheres.push_back(sInfo);
}