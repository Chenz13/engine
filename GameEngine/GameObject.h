#pragma once
#include "SDL.h"
#include "BoundingSphere.h"
#include "SimpleModel.h"

class GameObject
{
private:
	SimpleModel *model;
	BoundingSphere sphere;	
	glm::mat4 transform;
	glm::vec3 velocity;
	glm::vec3 rotation;
	glm::vec3 position;
	glm::vec3 initialVelocity;
	glm::vec3 accel;
	float angle;
	OpenGLRenderer* renderer;
public:

	GameObject();
	void OnInput(Uint32 event, SDL_Keycode key);
	void Update(double deltaTime);
	void Render();
	glm::mat4 GetTransform();
	glm::vec3 GetMovement();
	void SetMovement(glm::vec3 _movement);
	glm::vec3 GetRotation();
	void SetRotation(glm::vec3 _rotation);
	float GetAngle();
	void SetAngle(float _angle);
	BoundingSphere GetSphere();
	GameObject(SimpleModel *_model, BoundingSphere _sphere, OpenGLRenderer &_rend);
	~GameObject();
};

