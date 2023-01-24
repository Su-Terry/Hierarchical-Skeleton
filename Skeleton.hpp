#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <unordered_map>

#include "Exception.hpp"
#include "Bone.hpp"
#include "Shader.hpp"
#include "Controller.hpp"

class Skeleton {

public:
    Skeleton(std::unordered_map<std::string, Bone*> bones, const std::string& rootBoneId);
    ~Skeleton();

    void        update();
    void        rotate(GLfloat theta, std::string boneId);

    void        handleKeys(const std::array<bool, N_KEY>& keys);

    void                                            setShader(Shader* s) { shader = s; };

    const Bone*                                     getParentBone() const { return rootBone; };
    const std::string&                              getParentBoneId() const { return rootBoneId; };
    const std::unordered_map<std::string, Bone*>&   getBones() const { return bones; };
    Shader*                                         getShader() const { return shader; };

    Bone*                                           operator[](const std::string& id);

private:
    Bone*                                   rootBone;
    std::string                             rootBoneId;
    std::unordered_map<std::string, Bone*>  bones;
    Shader*                                 shader;

};
