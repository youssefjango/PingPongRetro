/*void render_background() {
	c32* pixel = (c32*)renderState.buffer_memory;
	for (int i = 0; i < renderState.height; i++) {
		for (int j = 0; j < renderState.width; j++) {
			//*pixel++ = j*i;
		}
	}
}*/
internal void clearScreen(u32 color) {
	u32* pixel = (u32*)renderState.buffer_memory;
	for (int i = 0; i < renderState.height; i++) {
		for (int j = 0; j < renderState.width; j++) {
			*pixel++ = color;
		}
	}
}



internal void draw_rect_pxl(int x0, int y0, int x1, int y1, u32 color) {
	
	x0 = clamp(0, x0, renderState.width);
	x1 = clamp(0, x1, renderState.width);
	y0 = clamp(0, y0, renderState.height);
	y1 = clamp(0, y1, renderState.height);

	for (int i = y0; i < y1; i++) {
		u32* pixel = (u32*)renderState.buffer_memory + x0 +  i * renderState.width;
		for (int j = x0; j < x1; j++) {
			*pixel++ = color;
		}
	}
}

internal void draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {
	
	//relative to width/height
	x *= renderState.height;
	y *= renderState.height;
	half_size_x *= renderState.height;
	half_size_y *= renderState.height;

	x += renderState.width / 2.f;
	y += renderState.height / 2.f;
	//transform to 4 points
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;
	draw_rect_pxl(x0, y0, x1, y1, color);
}