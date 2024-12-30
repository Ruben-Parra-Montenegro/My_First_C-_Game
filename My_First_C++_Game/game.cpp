#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input ->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_1_p = 0.f, player_1_dp, player_2_p = 0.f, player_2_dp;


internal void simulate_game(Input* input, float dt) {
	clear_screen(0x000000);

	float player_1_ddp = 0.f;
	if (is_down(BUTTON_W)) player_1_ddp += 2000;
	if (is_down(BUTTON_S)) player_1_ddp -= 2000;

	player_1_ddp -= player_1_dp * 10.f;

	player_1_p = player_1_p + player_1_dp * dt + player_1_ddp * dt * dt * .5f;
	player_1_dp = player_1_dp + player_1_ddp * dt;

	draw_rect(-85, player_1_p, 2, 16, 0xFF0000);
	draw_rect(0, 0, 1, 1, 0xFF0000);


	float player_2_ddp = 0.f;
	if (is_down(BUTTON_UP)) player_2_ddp += 2000;
	if (is_down(BUTTON_DOWN)) player_2_ddp -= 2000;

	player_2_ddp -= player_2_dp * 10.f;

	player_2_p = player_2_p + player_2_dp * dt + player_2_ddp * dt * dt * .5f;
	player_2_dp = player_2_dp + player_2_ddp * dt;

	draw_rect(85, player_2_p, 2, 16, 0xff0000);
	draw_rect(0, 0, 1, 1, 0xFF0000);

	

}