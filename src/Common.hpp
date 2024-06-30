#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <memory>

enum class WindowedMode { WINDOWED, FULLSCREEN };

#define NEAR_PLANE 0.005f
#define FAR_PLANE 500.0f

#define PI 3.141592653589793f
#define HALF_PI 1.57079632679f

#define ToRadian(x) (float)(((x) * PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / PI))

#define BLACK			glm::vec3(0,0,0)
#define WHITE			glm::vec3(1,1,1)
#define RED				glm::vec3(1,0,0)
#define GREEN			glm::vec3(0,1,0)
#define BLUE			glm::vec3(0,0,1)
#define YELLOW			glm::vec3(1,1,0)
#define PURPLE			glm::vec3(1,0,1)
#define GREY			glm::vec3(0.25f)

#define NRM_X_FORWARD	glm::vec3(1,0,0)
#define NRM_X_BACK		glm::vec3(-1,0,0)
#define NRM_Y_UP		glm::vec3(0,1,0)
#define NRM_Y_DOWN		glm::vec3(0,-1,0)
#define NRM_Z_FORWARD	glm::vec3(0,0,1)
#define NRM_Z_BACK		glm::vec3(0,0,-1)