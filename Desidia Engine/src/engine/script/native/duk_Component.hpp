/*
This is an object that handles all the ComponentCamera operations through JS code.
*/

#pragma once
#include "../../lib/duktape/duktape.h"

class Component;

class duk_Component {
	public:
		static Component* parseComponent(duk_context *ctx, duk_idx_t obj_idx);
		static void pushComponent(duk_context *ctx, const char* gameObjectName, const char* componentGroup, int index);
		static void pushComponents(duk_context *ctx, const char* gameObjectName, const char* componentGroup);
};