#include "Paddle.h"
#include "Ball.h"
#include "CONSTANTS.cpp"
#include "Button.h"

#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

enum GameMode {
	GM_Menu,
	GM_LevelMenu,
	GM_Gameplay
};
GameMode currentGM = GM_Menu;

Paddle* playerPaddle;
Paddle* enemyPaddle;
std::vector<Paddle*> paddlesList;
Ball* ball;


std::vector<Button*> buttonsPage1;
std::vector<Button*> buttonsPage2;

Button* current;
//Where all actors of the scene are initialized
internal void initializeActors() {
	Button* playBtn = new Button(playButton_Position.x, playButton_Position.y, hoverColor, firstPageButton_HalfSize, playTxt);
	current = playBtn;
	Button* quitBtn = new Button(quitButton_Position.x, quitButton_Position.y, defaultColor, firstPageButton_HalfSize, quitTxt);
	
	
	Button* PVEButton = new Button(PVEButton_Position.x, PVEButton_Position.y, defaultColor, secondPageButton_HalfSize, PVETxt);
	
	Button* P2VEButton = new Button(P2VEButton_Position.x, P2VEButton_Position.y, defaultColor, secondPageButton_HalfSize, P2VETxt);
	
	Button* P2VE2Button = new Button(P2VE2Button_Position.x, P2VE2Button_Position.y, defaultColor, secondPageButton_HalfSize, P2VE2Txt);
	
	Button* PVE2Button = new Button(PVE2Button_Position.x, PVE2Button_Position.y, defaultColor, secondPageButton_HalfSize, PVE2Txt);
	
	Button* PVPButton = new Button(PVPButton_Position.x, PVPButton_Position.y, defaultColor, secondPageButton_HalfSize, PVPTxt);
	
	Button* P2VPButton = new Button(P2VPButton_Position.x, P2VPButton_Position.y, defaultColor, secondPageButton_HalfSize, P2VPTxt);
	
	Button* P2VP2Button = new Button(P2VP2Button_Position.x, P2VP2Button_Position.y, defaultColor, secondPageButton_HalfSize, P2VP2Txt);
	

	buttonsPage1.push_back(playBtn);
	playBtn->addTag("play");
	buttonsPage1.push_back(quitBtn);
	quitBtn->addTag("quit");
	
	buttonsPage2.push_back(PVEButton);
	buttonsPage2.push_back(P2VEButton);
	buttonsPage2.push_back(P2VE2Button);
	buttonsPage2.push_back(PVE2Button);
	buttonsPage2.push_back(PVPButton);
	buttonsPage2.push_back(P2VPButton);
	buttonsPage2.push_back(P2VP2Button);
	
	
	
	playerPaddle = new Paddle(player_HorizontalPosition, player_StartingVerticalPosition
		, player_Color, initfriction, influenceFactor, 1.2f);
	enemyPaddle = new Paddle(enemy_HorizontalPosition, enemy_StartingVerticalPosition
		, enemy_Color, initfriction, influenceFactor, 1.2f);
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

internal void gameplay(Input* input, float dt) {
	playerPaddle->setAcceleration(0.0f);

	if (is_down(BUTTON_UP)) playerPaddle->setAcceleration(playerPaddle->getAcceleration().y + 2000.0f);
	else if (is_down(BUTTON_DOWN)) playerPaddle->setAcceleration(playerPaddle->getAcceleration().y - 2000.0f);

	//mode can be changed in the main menu
	enemyPaddle->respondToEnvirnment(ball, Hardcore);

	//ball side
	handleBall(ball, paddlesList, dt);


	handlePaddle(enemyPaddle, dt);
	handlePaddle(playerPaddle, dt);


	//Drawing ball's State
	draw_rect(ball->getPosition().x, ball->getPosition().y, ball->getRadius(), ball->getRadius(), ball->getColor());

	//GameMode Side
	if (ball->getPosition().x > arenaHalfSizeX + ball->getRadius() * RESPAWN_OFFSET_FACTOR || ball->getPosition().x < -arenaHalfSizeX - ball->getRadius() * RESPAWN_OFFSET_FACTOR) {

		ball->getPosition().x > arenaHalfSizeX + ball->getRadius() * RESPAWN_OFFSET_FACTOR ? playerPaddle->incrementScore() : enemyPaddle->incrementScore();

		ball->setPosition(originalBallX, originalBallY);
		//get the sign of the speed and flip it in order to send the ball to the winning round player
		ball->setSpeed(((ball->getSpeed().x > 0) - (ball->getSpeed().x <= 0)) * -1 * initialBallSpeedX, initialBallSpeedY);

	}

	//Drawing paddles' State
	draw_rect(playerPaddle->getPosition().x, playerPaddle->getPosition().y
		, playerPaddle->getHalfSizes().x, playerPaddle->getHalfSizes().y, playerPaddle->getColor());
	draw_rect(enemyPaddle->getPosition().x, enemyPaddle->getPosition().y
		, enemyPaddle->getHalfSizes().x, enemyPaddle->getHalfSizes().y, enemyPaddle->getColor());


	draw_number(playerPaddle->getScore(), -10, 40, 1.f, 0xbbffbb);
	draw_number(enemyPaddle->getScore(), 10, 40, 1.f, 0xbbffbb);
}

int hoverButtonIndex = 0;

internal void navigation(Input* input, std::vector<Button*> buttons) {
	if (pressed(BUTTON_LEFT)) {
		hoverButtonIndex = (hoverButtonIndex - 1) % buttons.size();
		if (current) {
			current->setColor(defaultColor);
		}
		current = buttons.at(hoverButtonIndex);
		current->setColor(hoverColor);


	}
	if (pressed(BUTTON_RIGHT)) {
		hoverButtonIndex = (hoverButtonIndex + 1) % buttons.size();
		if (current) {
			current->setColor(defaultColor);
		}
		current = buttons.at(hoverButtonIndex);
		current->setColor(hoverColor);

	}
}
internal void displayButtons(std::vector<Button*> buttons) {
	for (int i = 0; i < buttons.size(); i++) {
			draw_rect(buttons.at(i)->getPosition().x, buttons.at(i)->getPosition().y
				, buttons.at(i)->getHalfSizes().x, buttons.at(i)->getHalfSizes().y, buttons.at(i)->getColor());
		}
}
internal void mainMenu(Input* input) {
	navigation(input, buttonsPage1);
	if (pressed(BUTTON_ENTER)) {
		if (current->ContainsTag("play")) {
			currentGM = GM_LevelMenu;
			current = buttonsPage2.at(0);
			current->setColor(hoverColor);
		}
		else if (current->ContainsTag("quit")) {
			isRunning = false;
		}
	}
	displayButtons(buttonsPage1);
}
internal void levelMenu(Input* input) {
	navigation(input, buttonsPage2);
	displayButtons(buttonsPage2);

}
internal void simulate_game(Input* input, float dt) {
	//background
	clearScreen(0x0E2445);
	//arena rectangle
	draw_rect(0, 0, arenaHalfSizeX, arenaHalfSizeY, 0x000000);

	switch (currentGM) {
	case GM_Gameplay:
		gameplay(input, dt);
		break;
	case GM_Menu:
		mainMenu(input);
		break;
	case GM_LevelMenu:
		levelMenu(input);
	}

}