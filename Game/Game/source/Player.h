#pragma once
#include "ObjectBase.h"
#include "appframe.h"
#include "ApplicationMain.h"


class Player : public ObjectBase {
public:

	// インスタンス
	static Player* PlInstance;
	static Player* GetPlInstance() { return (Player*)PlInstance; }

	Player();
	~Player();

	bool Initialize()override;
	bool Terminate();
	bool Process()override;
	bool Render(int type) override;

	// ゲッター
	int GetHandle() { return handle; }

	

protected:

	// 透明度0.0~1.0
	float alpha;
};