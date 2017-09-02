#include "ComponentMesh.hpp"
#include "../../rendering/shader/ShaderManager.hpp"
#include "../../rendering/geometry/Mesh.hpp"
#include "../../Resources.hpp"
#include "../../rendering/material/Material.hpp"
#include <iostream>

ComponentMesh::ComponentMesh(std::string _model, std::string _material) : Component() {
	model = _model;
	material = _material;
}

void ComponentMesh::draw() {
	Resources::MATERIAL[material]->use();
	Resources::MODEL[model]->draw();
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

	Resources::loadModel(model);
	Resources::loadMaterial(material);

	Component* component = new ComponentMesh(model, material);
	return component;
}