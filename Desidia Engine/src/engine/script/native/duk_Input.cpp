#include "duk_Input.hpp"
#include "../../InputManager.hpp"

void duk_Input::init(duk_context *ctx) {
	duk_push_object(ctx);
	duk_push_c_function(ctx, duk_Input::isKeyDown, 1);
	duk_put_prop_string(ctx, -2, "isKeyDown");
	duk_push_c_function(ctx, duk_Input::isKeyDownCase, 1);
	duk_put_prop_string(ctx, -2, "isKeyDownCase");
	duk_push_c_function(ctx, duk_Input::isMouseButtonDown, 1);
	duk_put_prop_string(ctx, -2, "isMouseButtonDown");
	duk_push_c_function(ctx, duk_Input::getMouseMoveX, 0);
	duk_put_prop_string(ctx, -2, "getMouseMoveX");
	duk_push_c_function(ctx, duk_Input::getMouseMoveY, 0);
	duk_put_prop_string(ctx, -2, "getMouseMoveY");
	duk_put_global_string(ctx, "Input");
}

duk_ret_t duk_Input::isKeyDown(duk_context *ctx) {
	int nargs = duk_get_top(ctx);
	if (nargs != 1) return 0;

	int keyCode = duk_get_int(ctx, -1);

	duk_push_boolean(ctx, InputManager::isKeyDown(keyCode));
	return 1;
}

duk_ret_t duk_Input::isKeyDownCase(duk_context *ctx) {
	int nargs = duk_get_top(ctx);
	if (nargs != 1) return 0;

	int keyCode = duk_get_int(ctx, -1);

	duk_push_boolean(ctx, InputManager::isKeyDownCase(keyCode));
	return 1;
}

duk_ret_t duk_Input::isMouseButtonDown(duk_context *ctx) {
	int nargs = duk_get_top(ctx);
	if (nargs != 1) return 0;

	int buttonCode = duk_get_int(ctx, -1);

	duk_push_boolean(ctx, InputManager::mouseState[buttonCode]);
	return 1;
}

duk_ret_t duk_Input::getMouseMoveX(duk_context *ctx) {
	duk_push_number(ctx, InputManager::mouseMoveX);
	return 1;
}

duk_ret_t duk_Input::getMouseMoveY(duk_context *ctx) {
	duk_push_number(ctx, InputManager::mouseMoveY);
	return 1;
}