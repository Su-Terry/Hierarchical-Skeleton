#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <array>
#include <forward_list>

#include "Exception.hpp"
#include "Model.hpp"
#include "Matrix.hpp"
#include "Shader.hpp"

class Bone {

public:
    Bone(std::forward_list<Bone*> children, const std::string& name, const vec3& position, const vec3& orientation, const vec3& scale, const vec3& joint = vec3({0, 0, 0}), const int64_t color = 0xFFFFFF);
    ~Bone();

    void    rotate(GLfloat theta, Shader* shader);
    void    update(const mat4& transform, Shader* shader);
    void    rescale(const vec3& v, bool child = false);

    const std::string&              getName() const { return name; };
    Model*                          getModel() const { return model; };
    const std::forward_list<Bone*>& getChildren() const { return children; };

private:
    std::string                 name;
    Model*                      model;
    std::forward_list<Bone*>    children;

};
