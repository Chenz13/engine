#pragma once
#include "AbstractCamera.h"
#include <gtx\euler_angles.hpp>

class FPS_Camera :
	public AbstractCamera
{
public:
	FPS_Camera(void);
	~FPS_Camera(void);

	//update ViewMatrix
	void Update();

	//MOVEMENT

	//Forward Movement
	void Walk(const float _distance);
	//Horizontal Movement
	void Strafe(const float _distance);
	//Vertical Movement
	void Lift(const float _distance);


protected:
	float speed;
	glm::vec3 translation;


public: //ACCESSORS MUTATORS

	void SetTranslate(const glm::vec3& _trans_value) { translation = _trans_value; }
	glm::vec3 GetTranslation() const { return translation; }

	void SetSpeed(const float _speed) { speed = _speed; }
	const float GetSpeed() const { return speed; }
};

