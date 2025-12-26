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

global_variable float render_scale = 0.01f;

/*internal void draw_circle(int x, int y, int radius, u32 color) {
	x *= renderState.height * render_scale;
	y *= renderState.height * render_scale;
	radius *= renderState.height * render_scale;
	radius *= renderState.height * render_scale;

	x += renderState.width / 2.f;
	y += renderState.height / 2.f;

	int minX = clamp(0, x - radius, renderState.width - 1);
	int maxX = clamp(0, x + radius, renderState.width - 1);
	int minY = clamp(0, y - radius, renderState.height - 1);
	int maxY = clamp(0, y + radius, renderState.height - 1);
	u32* pixel = (u32*)renderState.buffer_memory;
	for (int i = minY; i <= maxY; i++) {
		for (int j = minX; j <= maxX; j++) {
			int dx = j - x;
			int dy = i - y;
			if (dx * dx + dy * dy <= radius * radius) {
				pixel[i * renderState.width + j] = color;
			}
		}
	}


}*/

internal void draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {
	
	//relative to width/height
	x *= renderState.height * render_scale;
	y *= renderState.height * render_scale;
	half_size_x *= renderState.height * render_scale;
	half_size_y *= renderState.height * render_scale;

	x += renderState.width / 2.f;
	y += renderState.height / 2.f;

	// Change to pixels
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;
	draw_rect_pxl(x0, y0, x1, y1, color);
}
internal void draw_number(int score, float x, float y, float size, u32 color) {
	float half_size = size / 2.0f;
	do {
		int digit = score % 10;
		score = score / 10;
		switch (digit) {
		case 0:
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x, y + 2.5f * size, half_size, size, color);
			draw_rect(x, y - 2.5f * size, half_size, half_size, color);
			break;
		case 1:
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			break;
		case 2:
			draw_rect(x, y + size * 2.5f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y, -size * 2.5f, 1.5f * size, color);
			draw_rect(x + size, y + size, half_size, half_size, color);
			draw_rect(x - size, y - size, half_size, half_size, color);
			break;
		case 3:
			draw_rect(x - half_size, y + size * 2.5f, half_size, 2.5f * size, color);
			draw_rect(x - half_size, y, size, 2.5f * size, color);
			draw_rect(x - half_size, y - size * 2.f, size, half_size, color);
			draw_rect(x + half_size, y, half_size, 2.5f * size, color);
			break;
		case 4:
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - size, y - size, half_size, 1.5f * size, color);
			draw_rect(x, y, half_size, half_size, color);
			break;
		case 5:
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, size * 1.5f, half_size, color);
			draw_rect(x - size, y + size, half_size, half_size, color);
			draw_rect(x + size, y - size, half_size, half_size, color);
			break;
		case 6:
			draw_rect(x + half_size, y + size * 2.5f, size, half_size, color);
			draw_rect(x + half_size, y, size, half_size, color);
			draw_rect(x + half_size, y - size * 2.f, size, half_size, color);
			draw_rect(x - size, y, half_size, size, color);
			draw_rect(x + size, y - size, half_size, half_size, color);
			break;
		case 7:
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - half_size, y + 2.f * size, size, half_size, color);
			break;
		case 8:
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x, y + size * 2.5f, half_size, half_size, color);
			draw_rect(x, y - size * 2.5f, half_size, half_size, color);
			draw_rect(x, y, half_size, half_size, color);
			break;
		case 9:
			draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
			draw_rect(x - half_size, y, size, half_size, color);
			draw_rect(x - half_size, y - size * 2.f, size, half_size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - size, y + size, half_size, half_size, color);
			break;
		}
		x -= size * 4.0f;

	} while (score);
}