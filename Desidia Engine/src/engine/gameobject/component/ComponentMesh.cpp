#include "ComponentMesh.hpp"
#include "../../rendering/shader/ShaderManager.hpp"
#include "../../rendering/geometry/Mesh.hpp"
#include "../../Resources.hpp"
#include "../../rendering/material/Material.hpp"
#include <iostream>

ComponentMesh::ComponentMesh(std::string _model, std::string _material, unsigned int _polygonMode) : Component() {
	model = _model;
	material = _material;
	polygonMode = _polygonMode;
}

void ComponentMesh::draw() {
	if (polygonMode == 1) {
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	Resources::MATERIAL[material]->use();
	Resources::MODEL[model]->draw();

	if (polygonMode == 1) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
	}
}

const char* ComponentMesh::getType() {
	return "ComponentMesh";
}

Component* ComponentMesh::parseJSON(const Value& value) {
	if (!value.HasMember("model") || !value.HasMember("material")) {
		cerr << "[SceneLoader] Necessary parameters weren't specified for a ComponentMesh." << endl;
		return nullptr;
	}

	std::string model = value["model"].GetString();
	std::string material = value["material"].GetString();
	unsigned int polygonMode = 0;
	if(value.HasMember("polygonMode"))
		polygonMode = value["polygonMode"].GetInt();

	Resources::loadModel(model);
	Resources::loadMaterial(material);

	Component* component = new ComponentMesh(model, material, polygonMode);
	return component;
}