#include "Scripts.hpp"
#include "ScriptNative.hpp"
#include "Script.hpp"
#include "ScriptContext.hpp"
#include "native/duk_Vector3.hpp"
#include "native/duk_GameObject.hpp"
#include "../Resources.hpp"
#include "../util/Time.hpp"
#include "../gameobject/GameObject.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

duk_context* context;

void pushNativeFunction(std::string name, duk_c_function function, int nargs) {
	duk_push_c_function(context, function, nargs);
	duk_put_global_string(context, ("native_" + name).c_str());
}

void fatalHandler(void *udata, const char* msg) {
	(void)udata;
	std::cout << "[JS FATAL ERROR] " << (msg ? msg : "No message") << std::endl;
}

std::map<std::string, Script*> Scripts::database = std::map<std::string, Script*>();

void Scripts::init() {
	context = duk_create_heap(NULL,
							  NULL,
							  NULL,
							  NULL,
							  fatalHandler);
	if (!context) {
		std::cerr << "Couldn't initialise the JavaScript context." << std::endl;
		abort();
	}

	duk_eval_string(context, "Engine = {}; Engine.Scripts = {}");
	for (ScriptNative::Function f : ScriptNative::functions) {
		pushNativeFunction(f.name, f.function, f.nargs);
		duk_eval_string(context, ("Engine."+f.name+" = native_"+f.name).c_str());
	}

	duk_Vector3::init(context);
	duk_GameObject::init(context);

	//duk_eval_string(context, "GameObject.setLocation('test', new Vector3(1, 2, 3))");
}

void Scripts::destroy() {
	duk_destroy_heap(context);
}

void Scripts::update() {
	duk_eval_string(context, ("Engine.Time = { delta: " + std::to_string(Time::delta) + " }").c_str());
}

void Scripts::execute(const char* command) {
	duk_push_string(context, command);
	if (duk_peval(context) != 0) {
		std::cout << "[JS ERROR] " << duk_safe_to_string(context, -1) << std::endl;
	}
	duk_pop(context);
}

void Scripts::executeScript(std::string path) {
	if (database.find(path) == database.end())
		return;

	database[path]->execute();
}

void Scripts::realiseScript(Script* script) {
	ScriptContext::setWorkScript(script);
	duk_get_global_string(context, "Engine");
	duk_get_prop_string(context, -1, "Scripts");
	duk_push_object(context);
	duk_push_object(context);
	duk_put_prop_string(context, -2, "eventListeners");
	duk_put_prop_string(context, -2, script->getPath().c_str());
	Scripts::execute(("Context.workScript = '"+script->getPath()+"'").c_str());
	Scripts::execute(script->getSource().c_str());
}

void Scripts::loadResource(std::string _path) {
	std::ifstream in(Resources::ROOT_PATH + _path);
	if (!in.is_open()) {
		std::cerr << "Failed to open a script file: " << _path << std::endl;
		return;
	}

	std::string code;

	in.seekg(0, std::ios::end);
	code.reserve(in.tellg());
	in.seekg(0, std::ios::beg);

	code.assign((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());

	Script* script = new Script(_path, code);
	database[_path] = script;
}