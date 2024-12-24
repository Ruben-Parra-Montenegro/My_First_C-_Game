//#include "util.cpp"

internal void clear_screen(u32 color) {
	unsigned int* pixel = (unsigned int*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

internal void draw_rect_pixels(int x0, int y0, int x1, int y1, u32 color) {

	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

global_variable float render_scale = 0.01f;

internal void draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {
	
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;
	// change to pixels
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;
	draw_rect_pixels(x0, y0, x1, y1, color);

}



//

internal void draw_circle(float x, float y, float radius, u32 color) {
	// Scale and translate to screen space
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	radius *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	// Determine bounding box in pixels
	int x_min = clamp(0, x - radius, render_state.width);
	int x_max = clamp(0, x + radius, render_state.width);
	int y_min = clamp(0, y - radius, render_state.height);
	int y_max = clamp(0, y + radius, render_state.height);

	// Iterate through bounding box pixels
	for (int py = y_min; py < y_max; py++) {
		for (int px = x_min; px < x_max; px++) {
			// Check if the pixel is inside the circle
			float dx = px - x;  // Distance from center in x
			float dy = py - y;  // Distance from center in y
			if (dx * dx + dy * dy <= radius * radius) {
				// If inside the circle, color the pixel
				u32* pixel = (u32*)render_state.memory + px + py * render_state.width;
				*pixel = color;
			}
		}
	}
}


