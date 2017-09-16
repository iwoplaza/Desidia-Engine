#include "duk_Vector3.hpp"
#include <iostream>
#include <string>

using namespace std;

void duk_Vector3::init(duk_context *ctx) {
	duk_push_c_function(ctx, duk_Vector3::constructor, DUK_VARARGS);
	duk_push_object(ctx);
	duk_push_c_function(ctx, duk_Vector3::toString, 0);
	duk_put_prop_string(ctx, -2, "toString");
	duk_push_c_function(ctx, duk_Vector3::addVec, 1);
	duk_put_prop_string(ctx, -2, "addVec");
	duk_push_c_function(ctx, duk_Vector3::multiplyVec, 1);
	duk_put_prop_string(ctx, -2, "multiplyVec");
	duk_push_c_function(ctx, duk_Vector3::multiply, 1);
	duk_put_prop_string(ctx, -2, "multiply");
	duk_put_prop_string(ctx, -2, "prototype");
	duk_put_global_string(ctx, "Vector3");
}

duk_ret_t duk_Vector3::constructor(duk_context *ctx) {
	//If this function wasn't run a a constructor, bail.
	if (!duk_is_constructor_call(ctx)) {
		return DUK_RET_TYPE_ERROR;
	}

	int args = duk_get_top(ctx);
	duk_push_this(ctx); // -> stack: [_x, _y, _z, this]
	if (args == 0)
		duk_push_number(ctx, 0);
	else
		duk_dup(ctx, 0);
	duk_put_prop_string(ctx, -2, "x");
	if (args <= 1)
		duk_push_number(ctx, 0);
	else
		duk_dup(ctx, 1);
	duk_put_prop_string(ctx, -2, "y");
	if (args <= 2)
		duk_push_number(ctx, 0);
	else
		duk_dup(ctx, 2);
	duk_put_prop_string(ctx, -2, "z");

	return 0;
}

duk_ret_t duk_Vector3::addVec(duk_context *ctx) {
	if (duk_get_top(ctx) != 1) return 0;

	duk_get_prop_string(ctx, 0, "x");
	double x0 = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 0, "y");
	double y0 = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 0, "z");
	double z0 = duk_get_number(ctx, -1);

	duk_push_this(ctx);
	duk_get_prop_string(ctx, -1, "x");
	double x1 = duk_get_number(ctx, -1);
	duk_pop(ctx);
	duk_get_prop_string(ctx, -1, "y");
	double y1 = duk_get_number(ctx, -1);
	duk_pop(ctx);
	duk_get_prop_string(ctx, -1, "z");
	double z1 = duk_get_number(ctx, -1);
	duk_pop(ctx);

	duk_get_global_string(ctx, "Vector3");
	duk_push_number(ctx, x0 + x1);
	duk_push_number(ctx, y0 + y1);
	duk_push_number(ctx, z0 + z1);
	duk_new(ctx, 3);

	return 1;
}

duk_ret_t duk_Vector3::multiplyVec(duk_context *ctx) {
	int nargs = duk_get_top(ctx);

	if (nargs != 1) return 0;

	duk_get_prop_string(ctx, 0, "x");
	double x0 = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 0, "y");
	double y0 = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 0, "z");
	double z0 = duk_get_number(ctx, -1);

	duk_push_this(ctx);
	duk_get_prop_string(ctx, -1, "x");
	double x1 = duk_get_number(ctx, -1);
	duk_pop(ctx);
	duk_get_prop_string(ctx, -1, "y");
	double y1 = duk_get_number(ctx, -1);
	duk_pop(ctx);
	duk_get_prop_string(ctx, -1, "z");
	double z1 = duk_get_number(ctx, -1);
	duk_pop(ctx);

	duk_get_global_string(ctx, "Vector3");
	duk_push_number(ctx, x0 * x1);
	duk_push_number(ctx, y0 * y1);
	duk_push_number(ctx, z0 * z1);
	duk_new(ctx, 3);

	return 1;
}

duk_ret_t duk_Vector3::multiply(duk_context *ctx) {
	if (duk_get_top(ctx) != 1) return 0;

	double a = duk_get_number(ctx, -1);

	duk_push_this(ctx);
	duk_get_prop_string(ctx, -1, "x");
	double x = duk_get_number(ctx, -1);
	duk_pop(ctx);
	duk_get_prop_string(ctx, -1, "y");
	double y = duk_get_number(ctx, -1);
	duk_pop(ctx);
	duk_get_prop_string(ctx, -1, "z");
	double z = duk_get_number(ctx, -1);
	duk_pop(ctx);

	duk_get_global_string(ctx, "Vector3");
	duk_push_number(ctx, x * a);
	duk_push_number(ctx, y * a);
	duk_push_number(ctx, z * a);
	duk_new(ctx, 3);

	return 1;
}

duk_ret_t duk_Vector3::toString(duk_context *ctx) {
	duk_push_this(ctx);
	duk_get_prop_string(ctx, -1, "x");
	string x = string(duk_safe_to_string(ctx, -1));
	duk_pop(ctx);
	duk_get_prop_string(ctx, -1, "y");
	string y = string(duk_safe_to_string(ctx, -1));
	duk_pop(ctx);
	duk_get_prop_string(ctx, -1, "z");
	string z = string(duk_safe_to_string(ctx, -1));
	duk_pop(ctx);
	string text = "[" + x + ", " + y + ", " + z + "]";
	duk_push_string(ctx, text.c_str());
	return 1;
}