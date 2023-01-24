#include "Controller.hpp"

Controller::Controller(GLFWwindow* window) : window(window), key() {
    std::cout << "[w][s] : move forward/backward\n[a][d] : move left/right\n"
    "[space][shift] : move up/down\n\n"
    "[1] : rotate head\n"
    "[2] : rotate upper left arm\n"
    "[3] : rotate upper right arm\n"
    "[4] : rotate lower left arm\n"
    "[5] : rotate lower right arm\n"
    "[6] : rotate upper left leg\n"
    "[7] : rotate upper right leg\n"
    "[8] : rotate lower left leg\n"
    "[9] : rotate lower right leg\n"
    "[0] : rotate pelvis\n\n"
    "[esc] : quit\n";
}

Controller::~Controller() {
}

void    Controller::update() {
    this->keyHandler();
}

void    Controller::keyHandler() {
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->window, GL_TRUE);
    for (size_t k = 0; k < N_KEY; ++k)
        this->keyUpdate(k);
}

void	Controller::keyUpdate(int k) {
    const short value = (glfwGetKey(this->window, k) == GLFW_PRESS);
    this->key[k] = value;
}
