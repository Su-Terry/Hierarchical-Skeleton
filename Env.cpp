#include "Env.hpp"

Env::Env() : character() {
    try {
        this->initGlfwEnvironment();
        this->initGlfwWindow(1024, 768);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw Exception::InitError("glad initialization failed");
        this->controller = new Controller(this->window.ptr);
        this->character = new Skeleton(this->createCharacterSkeleton(), "torso");
        this->setupController();
    } catch (const std::exception& err) {
        std::cout << err.what() << std::endl;
    }
}

Env::~Env() {
    delete this->character;
    delete this->controller;
    glfwDestroyWindow(this->window.ptr);
    glfwTerminate();
}

void Env::initGlfwEnvironment() {
	if (!glfwInit())
		throw Exception::InitError("glfw initialization failed");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void Env::initGlfwWindow( size_t width, size_t height ) {
    glfwWindowHint(GLFW_SAMPLES, 8);
	if (!(this->window.ptr = glfwCreateWindow(width, height, "Hierarchical Skeleton - 110550144", NULL, NULL)))
        throw Exception::InitError("glfwCreateWindow failed");
	glfwMakeContextCurrent(this->window.ptr);
	glfwSetInputMode(this->window.ptr, GLFW_STICKY_KEYS, 1);
    this->window.width = width;
    this->window.height = height;
}

void Env::setupController() {
}

std::unordered_map<std::string, Bone*> Env::createCharacterSkeleton() {
    std::unordered_map<std::string, Bone*> bones;
    bones["head"] = new Bone(
        std::forward_list<Bone*>{},
        "head",
        vec3({0, 0.425, 0}),
        mtls::normalize(vec3({1.0, 0.4, 0})),
        vec3({0.8, 0.85, 0.8}),
        vec3({0, -0.225, 0}),
        0xEEAD7E
    );
    bones["neck"] = new Bone(
        std::forward_list<Bone*>{ bones["head"] },
        "neck",
        vec3({0, 0.5, 0}),
        vec3({0, 0, 0}),
        vec3({0.3, 0.3, 0.3}),
        vec3({0, 0, 0}),
        0xEEAD7E
    );
    bones["lowerLeftLeg"] = new Bone(
        std::forward_list<Bone*>{{}},
        "lowerLeftLeg",
        vec3({0, -0.5, 0}),
        vec3({ 1, 0, 0 }),
        vec3({0.4, 1, 0.4}),
        vec3({0, 0.5, 0}),
        0x3F5D6A
    );
    bones["lowerRightLeg"] = new Bone(
        std::forward_list<Bone*>{{}},
        "lowerRightLeg",
        vec3({0, -0.5, 0}),
        vec3({ 1, 0, 0, }),
        vec3({0.4, 1, 0.4}),
        vec3({0, 0.5, 0}),
        0x3F5D6A
    );
    bones["leftKnee"] = new Bone(
        std::forward_list<Bone*>{ bones["lowerLeftLeg"] },
        "leftKnee",
        vec3({0, -0.5, 0}),
        vec3({0, 0, 0}),
        vec3({0.3, 0.3, 0.3}),
        vec3({0, 0, 0}),
        0xA4B37F
    );
    bones["rightKnee"] = new Bone(
        std::forward_list<Bone*>{ bones["lowerRightLeg"] },
        "rightKnee",
        vec3({0, -0.5, 0}),
        vec3({0, 0, 0}),
        vec3({0.3, 0.3, 0.3}),
        vec3({0, 0, 0}),
        0xA4B37F
    );
    bones["upperLeftLeg"] = new Bone(
        std::forward_list<Bone*>{ bones["leftKnee"] },
        "upperLeftLeg",
        vec3({0, -0.5, 0}),
        vec3({ 1, 0, 0 }),
        vec3({0.5, 1, 0.5}),
        vec3({0, 0.5, 0}),
        0x3F5D6A
    );
    bones["upperRightLeg"] = new Bone(
        std::forward_list<Bone*>{ bones["rightKnee"] },
        "upperRightLeg",
        vec3({0, -0.5, 0}),
        vec3({ 1, 0, 0 }),
        vec3({0.5, 1, 0.5}),
        vec3({0, 0.5, 0}),
        0x3F5D6A
    );
    bones["leftHip"] = new Bone(
        std::forward_list<Bone*>{ bones["upperLeftLeg"] },
        "leftHip",
        vec3({-0.3, -0.4, 0}),
        vec3({0, 0, 0}),
        vec3({0.3, 0.3, 0.3}),
        vec3({0, 0, 0}),
        0xA4B37F
    );
    bones["rightHip"] = new Bone(
        std::forward_list<Bone*>{ bones["upperRightLeg"] },
        "rightHip",
        vec3({0.3, -0.4, 0}),
        vec3({0, 0, 0}),
        vec3({0.3, 0.3, 0.3}),
        vec3({0, 0, 0}),
        0xA4B37F
    );
    bones["lowerLeftArm"] = new Bone(
        std::forward_list<Bone*>{{}},
        "lowerLeftArm",
        vec3({-0.4, 0, 0}),
        vec3({ 0, -1, 0 }),
        vec3({0.8, 0.35, 0.35}),
        vec3({0.4, 0, 0}),
        0xEEAD7E
    );
    bones["lowerRightArm"] = new Bone(
        std::forward_list<Bone*>{{}},
        "lowerRightArm",
        vec3({0.4, 0, 0}),
        vec3({ 0, 1, 0 }),
        vec3({0.8, 0.35, 0.35}),
        vec3({-0.4, 0, 0}),
        0xCDD4D2
    );
    bones["leftElbow"] = new Bone(
        std::forward_list<Bone*>{ bones["lowerLeftArm"] },
        "leftElbow",
        vec3({-0.5, 0, 0}),
        vec3({0, 0, 0}),
        vec3({0.3, 0.3, 0.3}),
        vec3({0, 0, 0}),
        0xA4B37F
    );
    bones["rightElbow"] = new Bone(
        std::forward_list<Bone*>{ bones["lowerRightArm"] },
        "rightElbow",
        vec3({0.5, 0, 0}),
        vec3({0, 0, 0}),
        vec3({0.3, 0.3, 0.3}),
        vec3({0, 0, 0}),
        0xA4B37F
    );
    bones["upperLeftArm"] = new Bone(
        std::forward_list<Bone*>{ bones["leftElbow"] },
        "upperLeftArm",
        vec3({ -0.45, 0, 0 }),
        vec3({ 0, 0, -1 }),
        vec3({ 0.9, 0.4, 0.4 }),
        vec3({ 0.45, 0, 0 }),
        0x408467
    );
    bones["upperRightArm"] = new Bone(
        std::forward_list<Bone*>{ bones["rightElbow"] },
        "upperRightArm",
        vec3({ 0.45, 0, 0 }),
        vec3({ 0, 0, 1 }),
        vec3({ 0.9, 0.4, 0.4 }),
        vec3({ -0.45, 0, 0 }),
        0x408467
    );
    bones["leftShoulder"] = new Bone(
        std::forward_list<Bone*>{ bones["upperLeftArm"] },
        "leftShoulder",
        vec3({-0.85, 0, 0}),
        vec3({0, 0, 0}),
        vec3({0.3, 0.3, 0.3}),
        vec3({0, 0, 0}),
        0xA4B37F
    );
    bones["rightShoulder"] = new Bone(
        std::forward_list<Bone*>{ bones["upperRightArm"] },
        "rightShoulder",
        vec3({0.85, 0, 0}),
        vec3({0, 0, 0}),
        vec3({0.3, 0.3, 0.3}),
        vec3({0, 0, 0}),
        0xA4B37F
    );
    bones["pelvis"] = new Bone(
        std::forward_list<Bone*>{{ bones["leftHip"], bones["rightHip"] }},
        "pelvis",
        vec3({0, -0.425, 0}),
        mtls::normalize(vec3({1, 0, 0})),
        vec3({0.95, 0.95, 0.8}),
        vec3({0, 0.1, 0}),
        0x43876A
    );
    bones["stomach"] = new Bone(
        std::forward_list<Bone*>{ bones["pelvis"] },
        "stomach",
        vec3({0, -0.5, 0}),
        vec3({0, 0, 0}),
        vec3({0.7, 0.7, 0.8}),
        vec3({0, 0, 0}),
        0xA4B37F
    );
    bones["torso"] = new Bone(
        std::forward_list<Bone*>{{ bones["neck"], bones["stomach"], bones["leftShoulder"], bones["rightShoulder"] }},
        "torso",
        vec3({0, 0.25, 0}),
        vec3({0, 0, 0}),
        vec3({1.5, 1, 1}),
        vec3({0, 0, 0}),
        0x0C1161
    );
    return bones;
}
