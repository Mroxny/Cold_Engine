#include "Window.h"

auto convertCharsToLPWSTR(const char* text) -> LPWSTR {
	size_t size = strlen(text) + 1;
	wchar_t* wtext = new wchar_t[size];


	size_t outSize;
	mbstowcs_s(&outSize, wtext, size, text, size - 1);
	return wtext;
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	try
	{
		Window wnd(800, 300, L"Cold Engine");


		MSG msg;
		BOOL gResult;

		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (gResult == -1) return -1;
		else return msg.wParam;
	}
	catch (const ColdWindowException& e)
	{
		MessageBox(nullptr, convertCharsToLPWSTR(e.what()), convertCharsToLPWSTR(e.GetType()), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, convertCharsToLPWSTR(e.what()), L"Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, L"No details available", L"Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}

