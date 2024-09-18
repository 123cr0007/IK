#include "ApplicationMain.h"
#include "Player.h"
#include "Camera.h"

Player* Player::PlInstance = nullptr;
Player::Player() {
	PlInstance = this;
}

Player::~Player() {
}

bool Player::Initialize() {

	Load("res/Lynette/Lynette.mv1", 1);
	alpha = 0.5f;
	return true;
}

bool Player::Terminate() {
	return true;
}

bool Player::Process() {


	return true;
}

bool Player::Render(int type) {

	// “§–¾“x
	MV1SetOpacityRate(handle, alpha);	// “§–¾“x‚ğİ’è

	MV1DrawModel(handle);
	return true;
}