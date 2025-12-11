#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

//Arena Data, to be added in futur class
float arenaHalfSizeX = 85, arenaHalfSizeY = 45;

//Player Data, to be added in a futur class with position update in future.
float player_VerticalLevel, speed;
float player_halfSizeY = 12.0f, player_halfSizeX = 2.5f;
float const friction = 10.0f;
float player_HorizontalPosition = -80.0f;
float influenceFactor = 1.0f;//dictates how influent the y speed is on the ball when hitting.
//Ball data, to be added in future ball class as well
float ballPositionX, ballPositionY, ballSpeedY, ballSpeedX = -100.0f, ballAcceleration;
float ballRadius = 1;
float const originalBallX = 0.0f, originalBallY = 0.0f;

internal void simulate_game(Input* input, float dt) {
	//background
	clearScreen(0x0E2445);
	//arena rectangle
	draw_rect(0, 0, arenaHalfSizeX, arenaHalfSizeY, 0x000000);

	float acceleration = 0.f;
	if (is_down(BUTTON_UP)) acceleration += 2000;
	else if (is_down(BUTTON_DOWN)) acceleration -= 2000;
	

	draw_rect(80, 0, 2.5, 12, 0x6C9D9E);
	
	//ball side
	
	ballPositionX += ballSpeedX * dt;
	ballPositionY += ballSpeedY * dt;

	if (ballPositionY + ballRadius > arenaHalfSizeY) {
		ballPositionY = arenaHalfSizeY - ballRadius;
		ballSpeedY *= -1;
	} else if (ballPositionY - ballRadius < - arenaHalfSizeY) {
		ballPositionY = - arenaHalfSizeY + ballRadius;
		ballSpeedY *= -1;
	}

	if (ballPositionX + ballRadius < player_HorizontalPosition + player_halfSizeX &&
		ballPositionX - ballRadius > player_HorizontalPosition - player_halfSizeX &&
		ballPositionY + ballRadius < player_VerticalLevel + player_halfSizeY &&
		ballPositionY - ballRadius > player_VerticalLevel - player_halfSizeY) {
		
		ballPositionX = player_HorizontalPosition + player_halfSizeX + ballRadius;
		ballSpeedX *= -1;
		ballSpeedY = influenceFactor * speed;
	}

	draw_rect(ballPositionX, ballPositionY, ballRadius, ballRadius, 0x00ff22);
	
	
	
	
	
	
	//
	//player side
	if (player_VerticalLevel + player_halfSizeY > arenaHalfSizeY) {
		player_VerticalLevel = arenaHalfSizeY - player_halfSizeY;
		speed = -speed;
	}
	else if (player_VerticalLevel - player_halfSizeY < -arenaHalfSizeY) {
		player_VerticalLevel = -arenaHalfSizeY + player_halfSizeY;
		speed = -speed;
	}
	acceleration -= speed * friction;
	player_VerticalLevel += speed * dt + acceleration * dt * dt * 0.5f;
	speed += acceleration * dt;
	
	//GameMode Side
	if (ballPositionX > arenaHalfSizeX + ballRadius * 1.5f || ballPositionX < - arenaHalfSizeX - ballRadius * 1.5f) { 
		//or to be split to take into account who won in future
		ballPositionX = originalBallX;
		ballPositionY = originalBallY;
		ballSpeedY = 0;
		ballSpeedX *= -1;
	}

	draw_rect(-80, player_VerticalLevel, player_halfSizeX, player_halfSizeY, 0x6C9D9E);
}