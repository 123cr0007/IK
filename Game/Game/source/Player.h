#pragma once
#include "ObjectBase.h"
#include "appframe.h"
#include "ApplicationMain.h"


class Player : public ObjectBase {
public:

	// �C���X�^���X
	static Player* PlInstance;
	static Player* GetPlInstance() { return (Player*)PlInstance; }

	Player();
	~Player();

	bool Initialize()override;
	bool Terminate();
	bool Process()override;
	bool Render(int type) override;

	// �Q�b�^�[
	int GetHandle() { return handle; }

	

protected:

	// �����x0.0~1.0
	float alpha;
};