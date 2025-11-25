#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_posX = 0.f;
float player_posY = 0.f;


internal void simulate_game(Input* input, float dt) {
	clearScreen(0xff5500);
	float speed = 50.f;
	if (is_down(BUTTON_UP))
		player_posY += speed * dt;
	if (is_down(BUTTON_DOWN)) player_posY -= speed * dt;
	if (is_down(BUTTON_RIGHT)) player_posX += speed * dt;
	if (is_down(BUTTON_LEFT)) player_posX -= speed * dt;
	
	draw_rect(player_posX, player_posY, 1, 1, 0x00ff22);
	draw_rect(30, 30, 5, 5, 0xffff22);
	draw_rect(-20, 20, 8, 3, 0xffff22);
}