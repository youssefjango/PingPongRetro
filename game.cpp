#include "Paddle.h"
#include "Ball.h"
#include "CONSTANTS.cpp"
#include "Button.h"
#include <algorithm> 

#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

enum GameMode {
	GM_Menu,
	GM_LevelMenu,
	GM_AIOption,
	GM_Gameplay
};
GameMode currentGM = GM_Menu;

Paddle* mainPlayerPaddle;
//second here means second teamate of the main player
Paddle* optionalSecondPaddle;
Paddle* mainEnemyPaddle;
//fourth here means second teamate of the main enemy
Paddle* optionalFourthPaddle;
std::vector<Paddle*> paddlesList;
Ball* ball;


std::vector<Button*> buttonsPage1;
std::vector<Button*> buttonsPage2;

Button* current;
//Where all actors of the scene are initialized
internal void initializeMenu() {
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

	//mode can be changed in the main men

	//ball side
	handleBall(ball, paddlesList, dt);
	//Drawing ball's State
	draw_rect(ball->getPosition().x, ball->getPosition().y, ball->getRadius(), ball->getRadius(), ball->getColor());

	//Win/Loss Event
	if (ball->getPosition().x > arenaHalfSizeX + ball->getRadius() * RESPAWN_OFFSET_FACTOR || ball->getPosition().x < -arenaHalfSizeX - ball->getRadius() * RESPAWN_OFFSET_FACTOR) {

		ball->getPosition().x > arenaHalfSizeX + ball->getRadius() * RESPAWN_OFFSET_FACTOR ? mainPlayerPaddle->incrementScore() : mainEnemyPaddle->incrementScore();

		ball->setPosition(originalBallX, originalBallY);
		//get the sign of the speed and flip it in order to send the ball to the winning round player
		ball->setSpeed(((ball->getSpeed().x > 0) - (ball->getSpeed().x <= 0)) * -1 * initialBallSpeedX, initialBallSpeedY);
		for (Paddle* p : paddlesList) {
			p->setPosition(p->getPosition().x, 0.0f);
		}
	}

	int blueScore = 0;
	int redScore = 0;
	for (Paddle* p : paddlesList) {
		if (p->ContainsTag("blue")) {
			blueScore += p->getScore();
		}
		else if (p->ContainsTag("red")) {
			redScore += p->getScore();
		}
		if (p->getDownControls() != UNDEFINED || p->getDownControls() != UNDEFINED) {
			p->setAcceleration(0.0f);
			if (is_down(p->getUpControls())) p->setAcceleration(p->getAcceleration().y + 2000.0f);
			else if (is_down(p->getDownControls())) p->setAcceleration(p->getAcceleration().y - 2000.0f);
		}
		else {
			p->respondToEnvirnment(ball);
		}
		handlePaddle(p, dt);
		//Drawing paddles' State
		draw_rect(p->getPosition().x, p->getPosition().y
		, p->getHalfSizes().x, p->getHalfSizes().y, p->getColor());
	}


	draw_number(blueScore, -10, 40, 1.f, 0x2C4E72);
	draw_number(redScore, 10, 40, 1.f, 0xB5514D);
}

int hoverButtonIndex = 0;

internal void navigate(Input* input, std::vector<Button*> buttons) {
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
		std::string text = buttons.at(i)->getText();
		std::transform(text.begin(), text.end(), text.begin(), ::toupper);
		draw_text(text.c_str(), buttons.at(i)->getPosition().x, buttons.at(i)->getPosition().y
			, buttons.at(i)->getHalfSizes().x, buttons.at(i)->getHalfSizes().y, buttons.at(i)->getColor());
		
		}
}
internal void mainMenu(Input* input) {
	navigate(input, buttonsPage1);
	if (pressed(BUTTON_ENTER)) {
		if (current->ContainsTag("play")) {
			currentGM = GM_LevelMenu;
			hoverButtonIndex = 0;
			current = buttonsPage2.at(hoverButtonIndex);
			current->setColor(hoverColor);
		}
		else if (current->ContainsTag("quit")) {
			isRunning = false;
		}
	}
	displayButtons(buttonsPage1);
}

internal void initializeActors(bool isAIMainEnemy) {
	mainPlayerPaddle = new Paddle(player_HorizontalPosition, player_StartingVerticalPosition
		, player_Color, initfriction, influenceFactor, 1.2f);
	mainPlayerPaddle->setControls(BUTTON_W, BUTTON_S);
	mainPlayerPaddle->addTag("blue");

	mainEnemyPaddle = new Paddle(enemy_HorizontalPosition, enemy_StartingVerticalPosition
		, enemy_Color, initfriction, influenceFactor, 1.2f);
	(isAIMainEnemy) ? mainEnemyPaddle->setBrain() : mainEnemyPaddle->setControls(BUTTON_UP, BUTTON_DOWN);
	mainEnemyPaddle->addTag("red");
	paddlesList.push_back(mainPlayerPaddle);
	paddlesList.push_back(mainEnemyPaddle);
	ball = new Ball(originalBallX, originalBallY, ballColor, ballRadius);
	ball->setSpeed(initialBallSpeedX, initialBallSpeedY);
}
internal void initializeOptionalPaddles(bool isSecond ,bool isFourth, bool isSecondAI, bool isFourthAI) {
	optionalSecondPaddle = isSecond ? new Paddle(secondPlayer_HorizontalPosition, player_StartingVerticalPosition
		, player_Color, initfriction, influenceFactor, 1.2f) : nullptr;
	if (isSecond) {
		optionalSecondPaddle->addTag("blue");

		isSecondAI ? optionalSecondPaddle->setBrain() : optionalSecondPaddle->setControls(BUTTON_F, BUTTON_V);
		paddlesList.push_back(optionalSecondPaddle);
		
	}
	optionalFourthPaddle = isFourth ? new Paddle(fourthPlayer_HorizontalPosition, player_StartingVerticalPosition
		, enemy_Color, initfriction, influenceFactor, 1.2f) : nullptr;

	if (isFourth) {
		optionalFourthPaddle->addTag("red");
		isFourthAI ? optionalFourthPaddle->setBrain() : optionalFourthPaddle->setControls(BUTTON_O, BUTTON_L);
		paddlesList.push_back(optionalFourthPaddle);
	}

}

internal void levelMenu(Input* input) {
	navigate(input, buttonsPage2);
	if (pressed(BUTTON_ENTER)) {
		

		//default minimum actors that will be initialized
		initializeActors(current->getText() == P2VETxt || current->getText() == PVETxt 
			|| current->getText() == P2VE2Txt || current->getText() == PVE2Txt);
		initializeOptionalPaddles(current->getText() == P2VETxt || current->getText() == P2VE2Txt
			|| current->getText() == P2VPTxt || current->getText() == P2VP2Txt
			, current->getText() == P2VE2Txt || current->getText() == PVE2Txt || current->getText() == P2VP2Txt
			, false
			, current->getText() == P2VE2Txt || current->getText() == PVE2Txt);

		currentGM = GM_Gameplay;
		current->setColor(defaultColor);
		current = nullptr;
		hoverButtonIndex = 0;
	}
	displayButtons(buttonsPage2);

}
/*
The Following starting code is for a future implementation of the selection of each AI mode of the paddles, for now it will
be a random one for each paddle
if (current->getText() == PVETxt) {
			currentGM = GM_AIOption;
		}
		else if (current->getText() == P2VETxt) {
			currentGM = GM_AIOption;
		}
		else if (current->getText() == P2VE2Txt) {
			currentGM = GM_AIOption;
		}
		else if (current->getText() == PVE2Txt) {
			currentGM = GM_AIOption;
		}
		else if (current->getText() == PVPTxt) {
			currentGM = GM_Gameplay;
		}
		else if (current->getText() == P2VPTxt) {
			currentGM = GM_Gameplay;
		}
		else if (current->getText() == P2VP2Txt) {
			currentGM = GM_Gameplay;
		}*/



internal void simulate_game(Input* input, float dt) {
	//background
	
	//arena rectangle
	

	switch (currentGM) {
	case GM_Gameplay:
		clearScreen(0x7A0080);
		draw_rect(0, 0, arenaHalfSizeX, arenaHalfSizeY, 0x000000);
		gameplay(input, dt);
		break;
	case GM_Menu:
		clearScreen(0x7A0080);
		draw_rect(0, 0, arenaHalfSizeX, arenaHalfSizeY, 0x000000);
		mainMenu(input);
		break;
	case GM_LevelMenu:
		clearScreen(0x7A0080);
		draw_rect(0, 0, arenaHalfSizeX, arenaHalfSizeY, 0x000000);
		levelMenu(input);
	}

}