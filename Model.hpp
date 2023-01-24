#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <stack>

#include "Exception.hpp"
#include "Matrix.hpp"
#include "Shader.hpp"
#include "utils.hpp"

class Model {

public:
    Model(const vec3& position, const vec3& orientation, const vec3& scale, const vec3& joint, const int64_t color);
    ~Model();

    void            rotate(const vec3& orientation, GLfloat theta);
    void            update(const mat4& parentTransform, Shader* shader);
    void            render(Shader* shader);

    mat4            popMatrix();
    void            pushMatrix() { stack.push(stack.top()); };
    void            pushMatrix(const mat4& mat) { stack.push(mat); };

    const GLuint&   getVao() const { return vao; };
    const mat4&     getTransform() const { return stack.top(); };
    const vec3&     getPosition() const { return position; };
    const vec3&     getOrientation() const { return orientation; };
    const vec3&     getScale() const { return scale; };
    const vec3&     getJoint() const { return joint; };
    const vec3&     getScaling() const { return scaling; };
    const vec3&     getWorldPosition() const { return worldPosition; };
    
    void            setPosition(const vec3& t) { position = t; };
    void            setOrientation(const vec3& r) { orientation = r; };
    void            setScale(const vec3& s) { scale = s; };
    void            setJoint(const vec3& j) { joint = j; };
    void            setScaling(const vec3& s) { scaling = s; };

private:
    int                 nIndices;           // the number of triangles of the model
    GLuint              vao;                // Vertex Array Object
    GLuint              vbo;                // Vertex Buffer Object
    GLuint              ebo;                // Element Buffer Object (or indices buffer object, ibo)

    std::stack<mat4>    stack;              // the stack matrix

    vec3                position;           // the position (parent local-space)
    vec3                orientation;        // the orientation (parent local-space)
    vec3                scale;              // the scale
    vec3                worldPosition;      // the position (world-space)

    vec3                joint;              // the joint around which the bone rotates (local-space)
    vec3                scaling;            // the value changed in animation as a modifier
    vec4                color;              // the color of the model

    void                initBufferObjects(int mode = GL_STATIC_DRAW);
    void                updateWorldPosition(const mat4& parentTransform);

};
