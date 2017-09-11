/*
	This file contains all the functions that are being pushed into the JS interpreter for use.
*/

#pragma once
#include "../lib/duktape/duktape.h"
#include <string>
#include <vector>

namespace ScriptNative {
	class Function {
		public:
			Function(std::string, duk_c_function, int _nargs);

			std::string name;
			duk_c_function function;
			int nargs;
	};
	extern std::vector<Function> functions;

	duk_ret_t print(duk_context* context);
	duk_ret_t gameObject_setLocation(duk_context* context);
}