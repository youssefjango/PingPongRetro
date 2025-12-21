#include "Paddle.h"
#include "Ball.h"
#include "CONSTANTS.cpp"

#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)



Paddle* playerPaddle;
Paddle* enemyPaddle;
std::vector<Paddle*> paddlesList;
Ball* ball;

//Where all actors of the scene are initialized
internal void initializeActors() {
	playerPaddle = new Paddle(player_HorizontalPosition, player_StartingVerticalPosition
		, player_Color, initfriction, influenceFactor, 2.0f);
	enemyPaddle = new Paddle(enemy_HorizontalPosition, enemy_StartingVerticalPosition
		, enemy_Color, initfriction, influenceFactor, 2.0f);
	paddlesList.push_back(playerPaddle);
	paddlesList.push_back(enemyPaddle);
	ball = new Ball(originalBallX, originalBallY, ballColor, ballRadius);
	ball->setSpeed(initialBallSpeedX, initialBallSpeedY);
}

//to be added as a function of the class Paddle in the futur.
void handlePaddle(Paddle* p, float dt) {
	if (p->getPosition().y + p->getHalfSizes().y > arenaHalfSizeY) {
		p->setPosition(p->getPosition().x, arenaHalfSizeY - player_halfSizeY);
		p->setSpeed(-p->getSpeed().y);
	}
	else if (p->getPosition().y - p->getHalfSizes().y < -arenaHalfSizeY) {
		p->setPosition(p->getPosition().x, -arenaHalfSizeY + player_halfSizeY);
		p->setSpeed(-p->getSpeed().y);
	}
	p->setAcceleration(p->getAcceleration().y - p->getSpeed().y * p->getFriction());
	p->setPosition(p->getPosition().x, p->getPosition().y + p->getSpeed().y * dt + p->getAcceleration().y * dt * dt * 0.5f);
	p->setSpeed(p->getSpeed().y + p->getAcceleration().y * dt);
}

bool isCollidingWithPaddle(Ball* b, Paddle* p) {
	return b->getPosition().x + b->getRadius() < p->getPosition().x + p->getHalfSizes().x &&
		   b->getPosition().x - b->getRadius() > p->getPosition().x - p->getHalfSizes().x &&
		   b->getPosition().y + b->getRadius() < p->getPosition().y + p->getHalfSizes().y &&
		   b->getPosition().y - b->getRadius() > p->getPosition().y - p->getHalfSizes().y;
}

//to be added as a function of the class ball in the futur.
void handleBall(Ball* b, std::vector<Paddle*> paddles,float dt) {
	b->setPosition(b->getPosition().x + b->getSpeed().x * dt, b->getPosition().y + b->getSpeed().y * dt);

	if (b->getPosition().y + b->getRadius() > arenaHalfSizeY) {
		b->setPosition(b->getPosition().x, arenaHalfSizeY - b->getRadius());
		b->setSpeed(b->getSpeed().x, -b->getSpeed().y);
	}
	else if (b->getPosition().y - b->getRadius() < -arenaHalfSizeY) {
		b->setPosition(b->getPosition().x, -arenaHalfSizeY + b->getRadius());
		b->setSpeed(b->getSpeed().x, -b->getSpeed().y);
	}
	for (Paddle* p : paddles) {
		if (isCollidingWithPaddle(b, p)) {
			Vector2D paddlePosition = p->getPosition();
			Vector2D ballPosition = b->getPosition();
			float newBallXPosition = (b->getSpeed().x > 0) ? 
				p->getPosition().x - p->getHalfSizes().x - b->getRadius() : 
				p->getPosition().x + p->getHalfSizes().x + b->getRadius();
			b->setPosition(newBallXPosition, b->getPosition().y);
			b->setSpeed(-b->getSpeed().x * p->getIncreaseHitFactor(), p->getInfluenceFactor() * p->getSpeed().y);
		}
	}

}

internal void simulate_game(Input* input, float dt) {
	//background
	clearScreen(0x0E2445);
	//arena rectangle
	draw_rect(0, 0, arenaHalfSizeX, arenaHalfSizeY, 0x000000);

	playerPaddle->setAcceleration(0.0f);

	if (is_down(BUTTON_UP)) playerPaddle->setAcceleration(playerPaddle->getAcceleration().y + 2000.0f);
	else if (is_down(BUTTON_DOWN)) playerPaddle->setAcceleration(playerPaddle->getAcceleration().y - 2000.0f);
	

	//draw_rect(80, 0, 2.5, 12, 0x6C9D9E);
	
	//ball side
	handleBall(ball, paddlesList, dt);
	
	
	handlePaddle(enemyPaddle, dt);
	handlePaddle(playerPaddle, dt);
	
	
	
	draw_rect(ball->getPosition().x, ball->getPosition().y, ball->getRadius(), ball->getRadius(), ball->getColor());

	//GameMode Side
	if (ball->getPosition().x > arenaHalfSizeX + ball->getRadius() * 1.5f || ball->getPosition().x < -arenaHalfSizeX - ball->getRadius() * RESPAWN_OFFSET_FACTOR) {
		//or to be split to take into account who won in future
		ball->setPosition(originalBallX, originalBallY);
		//get the sign of the speed and flip it in order to send the ball to the winning round player
		ball->setSpeed(((ball->getSpeed().x > 0) - (ball->getSpeed().x <= 0)) * -1 * initialBallSpeedX, initialBallSpeedY);
	}

	draw_rect(playerPaddle->getPosition().x, playerPaddle->getPosition().y
		, playerPaddle->getHalfSizes().x, playerPaddle->getHalfSizes().y, playerPaddle->getColor());
	draw_rect(enemyPaddle->getPosition().x, enemyPaddle->getPosition().y
		, enemyPaddle->getHalfSizes().x, enemyPaddle->getHalfSizes().y, enemyPaddle->getColor());
}