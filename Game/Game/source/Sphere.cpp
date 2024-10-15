#include "Sphere.h"
#include "Player.h"
#include "UI.h"

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

	ik = new IK();

	return true;
}

bool Sphere::Terminate() {
	

	return true;
}

bool Sphere::Process() {

	// �r�̒���
	float arm1Length = VSize(VSub(spheres[0].position, spheres[1].position));
	float arm2Length = VSize(VSub(spheres[1].position, spheres[2].position));

	// �^�[�Q�b�g�̈ʒu
	int sx = UI::GetUIInstance()->GetSX();
	int sy = UI::GetUIInstance()->GetSY();

	// �p�x�����ϐ�
	float arm1Lot = 0.0f;
	float arm2Lot = 0.0f;

	// IK
	ik->TwoBoneIK(spheres[0].position, arm1Length, arm2Length, 
		VGet(sx, sy, 0), arm1Lot, arm2Lot);

	// ���̂̈ʒu���X�V
	MATRIX arm1Mat = MGetIdent();
	MATRIX arm2Mat = MGetIdent();

	MATRIX arm1RotMat = MGetRotZ(arm1Lot);
	MATRIX arm2RotMat = MGetRotZ(arm2Lot);

	// �r1�̍s��v�Z
	arm1Mat = MMult(arm1Mat, arm1RotMat);
	arm2Mat = MMult(arm2Mat, arm2RotMat);

	// �r1�̈ʒu���X�V
	spheres[0].localMat = arm1Mat;
	spheres[1].localMat = arm2Mat;

	for (auto&& s : spheres) {

		MV1SetFrameUserLocalMatrix(charHandle, s.index, s.localMat);
		s.position = MV1GetFramePosition(charHandle, s.index);
	}

	Player::GetPlInstance()->SetHandle(charHandle);
	return true;
}

bool Sphere::Render(int type) {

	// ���̂̕`��
	for (auto&& s : spheres) {
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