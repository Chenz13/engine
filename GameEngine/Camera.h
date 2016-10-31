#pragma once
#include <GL\glew.h>
#include <vector>
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"

class Camera
{
private:
	GLuint modelHandle, viewHandle, projHandle;
	glm::vec3 positionVector, targetVector, upVector;
	glm::mat4 view, projection;
public:
	float fov = 60.0f;
	float aspectRatio = 800.0f / 600.0f; // Width of screen / height of screen
	float nearClipPlane = 0.1f;
	float farClipPlane = 100.0f;
	Camera();
	Camera(GLuint _program);
	void SetPositionVector(float _x, float _y, float _z);
	void SetTargetVector(float _x, float _y, float _z);
	void SetUpVector(float _x, float _y, float _z);
	void RenderModel(glm::mat4 _model);
	void Render();
	~Camera();
};
