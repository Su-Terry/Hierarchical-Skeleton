#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>

#include "Exception.hpp"
#include "Controller.hpp"
#include "Skeleton.hpp"
#include "Bone.hpp"

typedef struct  s_window {
    GLFWwindow* ptr;
    int         width;
    int         height;
}               t_window;

class Env {

public:
    Env();
    ~Env();

    const t_window& getWindow() const { return window; };
    Skeleton*       getCharacter() { return character; };
    Controller*     getController() { return controller; };

private:
    t_window    window;
    Controller* controller;
    Skeleton*   character;

    void        initGlfwEnvironment();
    void        initGlfwWindow(size_t width, size_t height);
    void        setupController();

    std::unordered_map<std::string, Bone*>  createCharacterSkeleton();
};
