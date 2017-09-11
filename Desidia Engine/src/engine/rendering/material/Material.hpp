#pragma once

#include "../../util/Color.hpp"
#include <string>

class Material {
	protected:
		std::string shader;

		Color diffuseColor;
		std::string diffuseMap;
	public:
		Material();

		void use();

		void setShader(std::string);
		void setDiffuseColor(Color);
		void setDiffuseMap(std::string);
		std::string getShader();
		Color getDiffuseColor();
		std::string getDiffuseMap();

		static Material* loadResource(std::string _path);
		static Material* loadFromString(std::string _code);
};