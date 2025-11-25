#include "Utility.cpp"

#include <windows.h>


struct Render_State {
	int height, width;
	void* buffer_memory;
	BITMAPINFO buffer_bminfo;
};
global_variable Render_State renderState;
global_variable bool isRunning = true;

#include "Renderer.cpp"




LRESULT CALLBACK window_cb(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY:
			//When we click on x, the game loop is ended.
			isRunning = false;
			break;
		case WM_SIZE:
			//Resize window, resize the buffer as well.
			RECT rect; 
			GetClientRect(hwnd, &rect);
			renderState.width = rect.right - rect.left;
			renderState.height = rect.bottom - rect.top;
			if (renderState.buffer_memory) {
				VirtualFree(renderState.buffer_memory, 0, MEM_RELEASE);
			}
			renderState.buffer_memory = VirtualAlloc(0, renderState.width * renderState.height * sizeof(unsigned int)
				, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			
			renderState.buffer_bminfo.bmiHeader.biSize = sizeof(renderState.buffer_bminfo.bmiHeader);
			renderState.buffer_bminfo.bmiHeader.biWidth = renderState.width;
			renderState.buffer_bminfo.bmiHeader.biHeight = renderState.height;
			renderState.buffer_bminfo.bmiHeader.biPlanes = 1;
			renderState.buffer_bminfo.bmiHeader.biBitCount = 32;
			renderState.buffer_bminfo.bmiHeader.biCompression = BI_RGB;
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
	HDC hdc = GetDC(window);
	while (isRunning) {
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)){
			TranslateMessage(&message);
			DispatchMessage(&message);
		
			//render_background();


			
			
			clearScreen(0xff5500);
			draw_rect(0,0,0.1,0.1, 0x00ff22);



			StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0,
				renderState.width, renderState.height, renderState.buffer_memory,
				&(renderState.buffer_bminfo), DIB_RGB_COLORS, SRCCOPY);
		}

	}
}