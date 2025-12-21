//DATA FOR ALL THE DEFAULT VALUES OF GAME

//Arena Data, to be added in futur class
float arenaHalfSizeX = 85, arenaHalfSizeY = 45;

float const initfriction = 10.0f;
//Player Data
float player_halfSizeY = 12.0f, player_halfSizeX = 2.5f;

float player_HorizontalPosition = -80.0f;
float player_StartingVerticalPosition = 0.0f;
u32 player_Color = 0x6C9D9E;

//Enemy Data
float enemy_halfSizeY = 12.0f, enemy_halfSizeX = 2.5f;

float enemy_HorizontalPosition = 80.0f;
float enemy_StartingVerticalPosition = 0.0f;
u32 enemy_Color = 0x6C9D9E;

float influenceFactor = 1.0f;//dictates how influent the y speed is on the ball when hitting.
//Ball data
float ballRadius = 1;
float initialBallSpeedY = 0.0f;
float initialBallSpeedX = 100.0f;

float const originalBallX = 0.0f, originalBallY = 0.0f;
u32 ballColor = 0x00ff22;
float RESPAWN_OFFSET_FACTOR = 1.5f;