#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"
struct Player : public GameObject
{
	Player();
	Player(const std::string& _modelPath, const std::string& _texturePath);
	~Player();

	void Update(float _dt) override;
	void Draw(float _dt, std::shared_ptr<ShaderProgram> _shader) override;
	void OnCollision(std::shared_ptr<Collider> _other);


	void ModifyHealth(float _healthChange);


	bool GetAlive() const;
	//If below a certain threshold, apply wounded texture to HUD
	float GetHealth() const;
	float GetAmmo() const;

private:

	float m_LastMouseX;
	float m_LastMouseY;
	float m_MoveSpeed;

	float m_Health;
	float m_Ammo;

	

};

#endif // !