#include "Cube.h"
Cube::~Cube() {
	std::cout << "Cube object deleted";
}


void Cube::MoveUp(const float &_jumpForce, bool &_isJumping, bool &_isFalling, const float &_jumpBoundY,const float &_deltaTime) {
	if (_isJumping == false) {

	}
	if (_isJumping == true) {
		if (this->GetPlayerPosition().y >= _jumpBoundY) {
			this->SetDirectionY(-1);
			this->SetPlayerVelocity(_jumpForce);
		}
		

		else {
			this->SetDirectionY(1);
			this->SetPlayerVelocity(_jumpForce);
			
		}
	}
	
	
}



void SetPlayerSprite() {

}

void GetPlayer

