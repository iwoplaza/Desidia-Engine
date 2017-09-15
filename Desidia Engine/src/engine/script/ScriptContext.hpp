#pragma once

class GameObject;
class Script;

class ScriptContext {
	public:
		static GameObject* gameObject;
		//The script that the engine is currently working on, for example registering event listeners
		//(for more see ComponentScript, ScriptNative and Script).
		static Script* workScript;

		static void setWorkScript(Script* script);
};