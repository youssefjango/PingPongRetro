#pragma once
struct Button_State {
	bool is_down;
	bool changed;
};

enum Controls {
	UNDEFINED,
	//player 1
	BUTTON_UP,
	BUTTON_DOWN,
	//player 2
	BUTTON_W,
	BUTTON_S,
	//player 3
	BUTTON_O,
	BUTTON_L,
	//player 4
	BUTTON_F,
	BUTTON_V,

	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_ENTER,

	BUTTON_COUNT, //should be in the last item
	
};

struct Input {
	Button_State buttons[BUTTON_COUNT]; // number of buttons
};