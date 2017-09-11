#include "ScriptNative.hpp"
#include "Scripts.hpp"
#include "../util/Vector3.hpp"
#include "ScriptContext.hpp"
#include <iostream>

using namespace std;

vector<ScriptNative::Function> ScriptNative::functions = {
	ScriptNative::Function("print", ScriptNative::print, 1),
	ScriptNative::Function("gameObject_setLocation", ScriptNative::gameObject_setLocation, DUK_VARARGS)
};

ScriptNative::Function::Function(string _name, duk_c_function _function, int _nargs) 
	: name(_name), function(_function), nargs(_nargs) {}

duk_ret_t ScriptNative::print(duk_context* context) {
	cout << "[JS]: " << duk_to_string(context, 0) << endl;
	return 0;
}

duk_ret_t ScriptNative::gameObject_setLocation(duk_context* context) {
	int n = duk_get_top(context);

	/*if (ScriptContext::gameObject == nullptr)
		return 0;*/

	cout << "Number of arguments: " << n << endl;

	duk_get_prop_string(context, 0, "x");
	cout << "X: " << duk_to_number(context, -1) << endl;
	duk_pop_2(context);

	duk_get_prop_string(context, 0, "y");
	cout << "Y: " << duk_to_number(context, -1) << endl;
	duk_pop_2(context);

	/*float x = 0, y = 0, z = 0;
	if (n == 1) {
		duk_get_prop_string(context, 0, "x");
		x = duk_to_number(context, -1);
		duk_pop_2(context);
		duk_get_prop_string(context, 0, "y");
		y = duk_to_number(context, -1);
		duk_pop_2(context);
		duk_get_prop_string(context, 0, "z");
		z = duk_to_number(context, -1);
		duk_pop_2(context);
	}
	else if (n == 3) {
		x = duk_to_number(context, 0);
		y = duk_to_number(context, 1);
		z = duk_to_number(context, 2);
	}
	Vector3 vec = Vector3(x, y, z);
	cout << "Set a location to: " << vec << endl;*/
	return 0;
}