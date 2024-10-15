#include "Sphere.h"
#include "Player.h"
#include "UI.h"

// インスタンスの生成
Sphere* Sphere::SpherelInstance = nullptr;
Sphere::Sphere() {

}

bool Sphere::Initialize() {
	
	// ハンドル
	charHandle = -1;
	if (Player::GetPlInstance() != nullptr) {
		charHandle = Player::GetPlInstance()->GetHandle();
	}

	GetFrameInfoFromName(charHandle, "左腕");	// 腰
	GetFrameInfoFromName(charHandle, "左ひじ");	// 腰
	GetFrameInfoFromName(charHandle, "左手首");	// 腰

	ik = new IK();

	return true;
}

bool Sphere::Terminate() {
	

	return true;
}

bool Sphere::Process() {

	// 腕の長さ
	float arm1Length = VSize(VSub(spheres[0].position, spheres[1].position));
	float arm2Length = VSize(VSub(spheres[1].position, spheres[2].position));

	// ターゲットの位置
	int sx = UI::GetUIInstance()->GetSX();
	int sy = UI::GetUIInstance()->GetSY();

	// 角度入れる変数
	float arm1Lot = 0.0f;
	float arm2Lot = 0.0f;

	// IK
	ik->TwoBoneIK(spheres[0].position, arm1Length, arm2Length, 
		VGet(sx, sy, 0), arm1Lot, arm2Lot);

	// 球体の位置を更新
	MATRIX arm1Mat = MGetIdent();
	MATRIX arm2Mat = MGetIdent();

	MATRIX arm1RotMat = MGetRotZ(arm1Lot);
	MATRIX arm2RotMat = MGetRotZ(arm2Lot);

	// 腕1の行列計算
	arm1Mat = MMult(arm1Mat, arm1RotMat);
	arm2Mat = MMult(arm2Mat, arm2RotMat);

	// 腕1の位置を更新
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

	// 球体の描画
	for (auto&& s : spheres) {
		DrawSphere3D(s.position, s.radius, 8, s.color, s.color, TRUE);
	}

	return true;
}

void Sphere::GetFrameInfoFromIndex(int chHandle, int index) {

	// 球体情報
	SphereInfo sInfo;

	// フレームの情報を取得
	sInfo.localMat = MV1GetFrameLocalMatrix(chHandle, index);
	sInfo.position = MV1GetFramePosition(chHandle, index);
	sInfo.index = index;
	sInfo.radius = 0.5f;

	spheres.push_back(sInfo);

}


void Sphere::GetFrameInfoFromName(int chHandle, const CHAR* name) {

	// 球体情報
	SphereInfo sInfo;

	// フレームの名前から情報を取る
	int index = MV1SearchFrame(chHandle, name);
	if (index == -1) {
		return;
	}

	// フレームの情報を取得
	sInfo.localMat = MV1GetFrameLocalMatrix(chHandle, index);
	sInfo.position = MV1GetFramePosition(chHandle, index);
	sInfo.index = index;
	sInfo.radius = 0.5f;

	spheres.push_back(sInfo);
}