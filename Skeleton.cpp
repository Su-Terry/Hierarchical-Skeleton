#include "Skeleton.hpp"

Skeleton::Skeleton(std::unordered_map<std::string, Bone*> bones, const std::string& rootBoneId) : bones(bones), rootBoneId(rootBoneId) {
    this->rootBone = this->bones[this->rootBoneId];
}

Skeleton::~Skeleton() {
    delete this->rootBone;
}

void Skeleton::update() {
    this->rootBone->update(mtls::mat4identity, this->shader);
}

void Skeleton::rotate(GLfloat theta, std::string boneId)
{
    this->bones[boneId]->rotate(theta, this->shader);
}

void Skeleton::handleKeys(const std::array<bool, N_KEY>& keys)
{
    if (keys[GLFW_KEY_1]) {
        rotate(0.01, "head");
    }
    if (keys[GLFW_KEY_2]) {
        rotate(0.01, "upperLeftArm");
    }
    if (keys[GLFW_KEY_3]) {
        rotate(0.01, "upperRightArm");
    }
    if (keys[GLFW_KEY_4]) {
        rotate(0.01, "lowerLeftArm");
    }
    if (keys[GLFW_KEY_5]) {
        rotate(0.01, "lowerRightArm");
    }
    if (keys[GLFW_KEY_6]) {
        rotate(0.01, "upperLeftLeg");
    }
    if (keys[GLFW_KEY_7]) {
        rotate(0.01, "upperRightLeg");
    }
    if (keys[GLFW_KEY_8]) {
        rotate(0.01, "lowerLeftLeg");
    }
    if (keys[GLFW_KEY_9]) {
        rotate(0.01, "lowerRightLeg");
    }
    if (keys[GLFW_KEY_0]) {
        rotate(0.01, "pelvis");
    }
}

Bone* Skeleton::operator[](const std::string& id) {
    if (this->bones.find(id) == this->bones.end())
        throw Exception::SkeletonMapAccessError(id);
    return (this->bones[id]);
}
