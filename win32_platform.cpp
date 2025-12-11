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
#include "PlatformCommon.cpp"
#include "game.cpp"





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

	Input input = {};
	float dt = 0.016666f;
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

	float performance_freq;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_freq = (float)perf.QuadPart;

	}

	while (isRunning) {
		MSG message;

		//reset input reading
		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			switch (message.message) {
				case WM_KEYUP:
				case WM_KEYDOWN: {
					u32 vk_code = (u32)message.wParam;
					bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk:{\
input.buttons[b].changed = is_down != input.buttons[b].is_down;\
input.buttons[b].is_down = is_down;\
} break;
					switch (vk_code) {
						process_button(BUTTON_UP, VK_UP);
						process_button(BUTTON_DOWN, VK_DOWN);
						process_button(BUTTON_LEFT, VK_LEFT);
						process_button(BUTTON_RIGHT, VK_RIGHT);
					}
				} break;

			default:
				TranslateMessage(&message);
				DispatchMessage(&message);
				break;
			}
		}
		
		simulate_game(&input, dt);

		StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0,
				renderState.width, renderState.height, renderState.buffer_memory,
				&(renderState.buffer_bminfo), DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER frame_final_time;
		QueryPerformanceCounter(&frame_final_time);
		dt = (float)(frame_final_time.QuadPart - frame_begin_time.QuadPart) / performance_freq;
		frame_begin_time = frame_final_time;
	}
}