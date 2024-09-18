#pragma once
#include "ObjectBase.h"
#include "appframe.h"
#include "ApplicationMain.h"

// �v���C���[�̑��x
constexpr auto PLAYER_SPEED = 3.0f;

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

protected:

};