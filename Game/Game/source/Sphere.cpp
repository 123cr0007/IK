#include "Sphere.h"
#include "Player.h"

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

	return true;
}

bool Sphere::Terminate() {
	

	return true;
}

bool Sphere::Process() {

	return true;
}

bool Sphere::Render(int type) {

	// 球体の描画
	for (auto& s : spheres) {
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