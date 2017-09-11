#include "Material.hpp"
#include "../../Resources.hpp"
#include "../shader/ShaderManager.hpp"
#include "../texture/Texture.hpp"
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>

using namespace rapidjson;

Material::Material() {
	shader = "_native/shaders/default.shader";
	diffuseColor = Color(1, 1, 1, 1);
	diffuseMap = "";
}

void Material::use() {
	ShaderManager::use(shader);
	Texture::bind(diffuseMap);
	glUniform1i(ShaderManager::getUniform("uMaterial.diffuseMap"), 0);
	glUniform1i(ShaderManager::getUniform("uMaterial.diffuseTextured"), diffuseMap != "");
	glUniform4f(ShaderManager::getUniform("uMaterial.diffuseColor"), diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
}

void Material::setShader(std::string _shader) {
	shader = _shader;
}

void Material::setDiffuseColor(Color _color) {
	diffuseColor = _color;
}

void Material::setDiffuseMap(std::string _texture) {
	diffuseMap = _texture;
}

std::string Material::getShader() {
	return shader;
}

Color Material::getDiffuseColor() {
	return diffuseColor;
}

std::string Material::getDiffuseMap() {
	return diffuseMap;
}

Material* Material::loadResource(std::string _path) {
	std::ifstream in(Resources::ROOT_PATH + _path);
	if (!in.is_open()) {
		std::cerr << "Failed to open a material file: " << _path << std::endl;
		return nullptr;
	}

	std::string code;

	in.seekg(0, std::ios::end);
	code.reserve(in.tellg());
	in.seekg(0, std::ios::beg);

	code.assign((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());

	return loadFromString(code.c_str());;
}

Material* Material::loadFromString(std::string _code) {
	Material* material = new Material();
	Document document;
	document.Parse(_code.c_str());

	if (document.HasMember("shader")) {
		material->shader = document["shader"].GetString();
		Resources::loadShader(material->shader);
	}
	if (document.HasMember("color")) {
		const Value& color = document["color"];
		material->diffuseColor = Color(color[0].GetFloat(), color[1].GetFloat(), color[2].GetFloat(), color[3].GetFloat());
	}
	if (document.HasMember("diffuseMap")) {
		material->diffuseMap = document["diffuseMap"].GetString();
		Texture::add(material->diffuseMap);
	}
	return material;
}