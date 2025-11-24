#include <windows.h>

bool isRunning = true;
LRESULT CALLBACK window_cb(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY:
			isRunning = false;
			break;
		default:
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);

	}
	return result;
}


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = window_cb;

	RegisterClass(&window_class);

	auto window = CreateWindow(window_class.lpszClassName, L"Ping Pong", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);

	while (isRunning) {
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)){
			TranslateMessage(&message);
			DispatchMessage(&message);
		
		}

	}
}