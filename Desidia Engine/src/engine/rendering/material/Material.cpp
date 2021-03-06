#include "Material.hpp"
#include "../../Resources.hpp"
#include "../shader/ShaderManager.hpp"
#include "../texture/Texture.hpp"
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>

using namespace rapidjson;

Material::Material(std::string _shader, Color _diffuseColor, std::string _diffuseMap, std::string _normalMap, int _shininess) {
	shader = _shader;
	diffuseColor = _diffuseColor;
	diffuseMap = _diffuseMap;
	normalMap = _normalMap;
	shininess = _shininess;
}
Material::Material(std::string _shader, Color _diffuseColor) : Material(_shader, _diffuseColor, "", "", 1) {}
Material::Material() : Material("_native/shaders/default.shader", Color(1, 1, 1, 1), "", "", 1) {}

void Material::use() {
	ShaderManager::use(shader);
	Texture::bind(diffuseMap, 0);
	Texture::bind(normalMap, 1);
	Texture::chooseActiveTexture(0);
	glUniform1i(ShaderManager::getUniform("uMaterial.diffuseMap"), 0);
	glUniform1i(ShaderManager::getUniform("uMaterial.normalMap"), 1);
	glUniform1i(ShaderManager::getUniform("uMaterial.diffuseMapped"), diffuseMap != "");
	glUniform1i(ShaderManager::getUniform("uMaterial.normalMapped"), normalMap != "");
	glUniform1i(ShaderManager::getUniform("uMaterial.shininess"), shininess);
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

void Material::setNormalMap(std::string _texture) {
	normalMap = _texture;
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

std::string Material::getNormalMap() {
	return normalMap;
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
	if (document.HasMember("diffuseColor")) {
		const Value& color = document["diffuseColor"];
		material->diffuseColor = Color(color[0].GetFloat(), color[1].GetFloat(), color[2].GetFloat(), color[3].GetFloat());
	}
	if (document.HasMember("diffuseMap")) {
		material->diffuseMap = document["diffuseMap"].GetString();
		Texture::add(material->diffuseMap);
	}
	if (document.HasMember("normalMap")) {
		material->normalMap = document["normalMap"].GetString();
		Texture::add(material->normalMap);
	}
	if (document.HasMember("shininess")) {
		material->shininess = document["shininess"].GetInt();
		if (material->shininess < 0) material->shininess = 0;
	}
	return material;
}