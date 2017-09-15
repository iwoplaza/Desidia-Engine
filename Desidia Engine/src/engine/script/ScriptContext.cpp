#include "ScriptContext.hpp"

GameObject* ScriptContext::gameObject;
Script* ScriptContext::workScript;

void ScriptContext::setWorkScript(Script* script) {
	workScript = script;
}