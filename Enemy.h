#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "GameObject.h"
struct Enemy : public GameObject
{

	Enemy();
	Enemy(const std::string& _modelPath, const std::string& _texturePath);
	~Enemy();

	void Update(float _dt) override;
	void Draw(float _dt, std::shared_ptr<ShaderProgram> _shader) override;


private:
	bool m_Alerted{ false };



};

#endif 

