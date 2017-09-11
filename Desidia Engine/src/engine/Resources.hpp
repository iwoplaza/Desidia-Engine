#pragma once
#include <string>
#include <map>
#include <vector>

class Mesh;
class Font;
class Material;

class Resources {
	protected:
		std::map<std::string, std::vector<std::string>> resourcesToLoad;
	public:
		Resources();
		~Resources();

		void loadFromFile(const char* _path);
		void loadFromString(const char* _code);
		void perform();

		static std::string ROOT_PATH;
		static std::map<std::string, Mesh*> MODEL;
		static std::map<std::string, Font*> FONT;
		static std::map<std::string, Material*> MATERIAL;
		static void loadModel(std::string key);
		static void loadFont(std::string key);
		static void loadMaterial(std::string key);
		static void loadScript(std::string key);
		static void loadShader(std::string key);
};