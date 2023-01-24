#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include <string>
#include <array>

#include "Exception.hpp"

#define N_KEY GLFW_KEY_LAST + 1

class Controller {

public:
    Controller(GLFWwindow* window);
    ~Controller();

    void            update();

    bool            getKeyPressed(int k) const { return key[k]; };

    const std::array<bool, N_KEY>&  getKeys() const { return key; };

private:
    GLFWwindow*             window;
    std::array<bool, N_KEY> key;

    void            keyHandler();
    void            keyUpdate(int k);

};
