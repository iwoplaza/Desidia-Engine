#include "PopUp.hpp"
#include <Windows.h>

namespace PopUp {
	void error(const wchar_t* msg) {
		MessageBox(0, LPCWSTR(msg), L"Error", 0);
	}
}