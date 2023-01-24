#include "Model.hpp"

Model::Model(const vec3& position, const vec3& orientation, const vec3& scale, 
    const vec3& joint, const int64_t color) : position(position), 
    orientation(orientation), scale(scale), joint(joint), color(hex2vec(color)) {
    this->nIndices = 0;
    this->initBufferObjects(GL_STATIC_DRAW);
    this->pushMatrix(mtls::mat4identity);
    this->worldPosition = vec3({0, 0, 0});
}

Model::~Model() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
    glDeleteBuffers(1, &this->ebo);
    while (!this->stack.empty())
        this->stack.pop();
}

mat4 Model::popMatrix() {
    mat4 top = this->stack.top();
    this->stack.pop();
    return (top);
};

void Model::rotate(const vec3& axis, GLfloat theta)
{
    mat4 rot = mtls::mat4identity;
    mtls::rotate(rot, theta, axis);
    vec4 tmp({ this->orientation[0], this->orientation[1], this->orientation[2], 1.0 });
    tmp = rot * tmp;
    this->orientation(0) = tmp[0];
    this->orientation(1) = tmp[1];
    this->orientation(2) = tmp[2];
    this->orientation = mtls::normalize(this->orientation);
}

void Model::update(const mat4& parentTransform, Shader* shader) {
    this->pushMatrix();
    mtls::translate(this->stack.top(), this->position);
    mtls::rotate(this->stack.top(), orientation*0.5, this->joint);
    this->stack.top() = this->stack.top() * parentTransform;
    this->pushMatrix();
    this->updateWorldPosition(parentTransform);
    mtls::scale(this->stack.top(), this->scale + this->scaling);
    this->render(shader);
    this->popMatrix();
}

void Model::render(Shader* shader) {
    shader->setVec4UniformValue("customColor", color);
    shader->setMat4UniformValue("model", this->stack.top());
    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, this->nIndices, GL_UNSIGNED_INT, 0);
}

void Model::updateWorldPosition(const mat4& parentTransform) {
    this->worldPosition = static_cast<vec3>(this->stack.top().transpose() * vec4({0,0,0,1}));
}

void Model::initBufferObjects(int mode) {
    std::vector<GLfloat>    vertices;
    std::vector<GLuint>     indices;

    createSphere(vertices, indices, 0.6f, 4, 40);
    this->nIndices = indices.size();

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);

    glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), mode);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), mode);
	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
