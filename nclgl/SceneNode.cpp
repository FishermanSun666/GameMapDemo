#include "SceneNode.h"

SceneNode::SceneNode(Mesh* mesh, Vector4 colour) {
	this->mesh = mesh;
	this->colour = colour;
	boundingRadius = 10.0f;
	distanceFromCamera = 0.0f;
	texture = 0;
	parent = NULL;
	modelScale = Vector3(1, 1, 1);
}

SceneNode::~SceneNode(void) {
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete children[i];
	}
	if (mesh) {
		delete mesh;
	}
}

void SceneNode::AddChild(SceneNode* s) {
	children.push_back(s);
	s->parent = this;
}

void SceneNode::Draw(OGLRenderer& r) {
	if (mesh) {
		mesh->Draw();
	}
}

void SceneNode::DrawShadow(OGLRenderer& r) {
	if (mesh) {
		r.UpdateModelMatrix(worldTransform * Matrix4::Scale(modelScale));
		r.UpdateShaderMatrices();
		mesh->Draw();
	}
}

void SceneNode::Update(float dt) {
	if (parent) {
		worldTransform = parent->worldTransform * transform;
	}
	else {
		worldTransform = transform;
	}
	for (auto i = children.begin(); i != children.end(); ++i) {
		(*i)->Update(dt);
	}
}