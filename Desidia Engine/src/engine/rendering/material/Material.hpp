#pragma once

#include "../../util/Color.hpp"
#include <string>

class Material {
	protected:
		std::string shader;

		Color diffuseColor;
		std::string diffuseMap;
		std::string normalMap;
		int shininess;
	public:
		Material();

		void use();

		void setShader(std::string);
		void setDiffuseColor(Color);
		void setDiffuseMap(std::string);
		void setNormalMap(std::string);
		std::string getShader();
		Color getDiffuseColor();
		std::string getDiffuseMap();
		std::string getNormalMap();

		static Material* loadResource(std::string _path);
		static Material* loadFromString(std::string _code);
};