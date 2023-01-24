#pragma once

#include <glad/glad.h>

#include <cmath>
#include <iostream>
#include <string>
#include <fstream>

#include "Exception.hpp"
#include "Matrix.hpp"
#include "Controller.hpp"

class Camera {

public:
    Camera(float fov, float aspect);
    Camera(const Camera& rhs);
    Camera& operator=(const Camera& rhs);
    ~Camera();

    void            handleKeys(const std::array<bool, N_KEY>& keys);

    void            setFov(float fov);
    void            setAspect(float aspect);

    const mat4&     getProjectionMatrix() const { return projectionMatrix; };
    const mat4&     getViewMatrix() const { return viewMatrix; };
    const float     getFov() const { return fov; };
    const float     getAspect() const { return aspect; };
    const vec3&     getPosition() const { return position; };
    const vec3&     getTarget() const { return target; };

    static mat4     createPerspectiveProjectionMatrix(float fov, float aspect, float near = 0.1, float far = 100.0);

private:
    mat4    projectionMatrix;
    mat4    viewMatrix;
    float   fov;
    float   aspect;
    vec3    position;
    vec3    target;
};
