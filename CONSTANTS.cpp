//DATA FOR ALL THE DEFAULT VALUES OF GAME

//Arena Data, to be added in futur class
float arenaHalfSizeX = 85, arenaHalfSizeY = 45;

float const initfriction = 10.0f;
//Player Data
float player_halfSizeY = 12.0f, player_halfSizeX = 2.5f;

float player_HorizontalPosition = -80.0f;
float player_StartingVerticalPosition = 0.0f;

float secondPlayer_HorizontalPosition = -40.0f;
float fourthPlayer_HorizontalPosition = 40.0f;
u32 player_Color = 0x6C9D9E;

//Enemy Data
float enemy_halfSizeY = 12.0f, enemy_halfSizeX = 2.5f;

float enemy_HorizontalPosition = 80.0f;
float enemy_StartingVerticalPosition = 0.0f;
u32 enemy_Color = 0xB5514D;

float influenceFactor = 1.0f;//dictates how influent the y speed is on the ball when hitting.
//Ball data
float ballRadius = 1;
float initialBallSpeedY = 0.0f;
float initialBallSpeedX = 100.0f;

float const originalBallX = 0.0f, originalBallY = 0.0f;
u32 ballColor = 0x00ff22;
float RESPAWN_OFFSET_FACTOR = 1.5f;



//Buttons Data
u32 hoverColor = 0x6c25be;
u32 defaultColor= 0x2596be;
Vector2D firstPageButton_HalfSize = {25.0f, 10.0f};
std::string playTxt = "play";
Vector2D playButton_Position = { 30.0f, 15.0f };
std::string quitTxt = "quit";
Vector2D quitButton_Position = { -30.0f, -15.0f };



Vector2D secondPageButton_HalfSize = {10.0f, 3.0f};
std::string PVETxt = "PVE";
Vector2D PVEButton_Position = {-50.0f, 0.0f};
std::string P2VETxt = "2PVE";
Vector2D P2VEButton_Position = { -25.0f, 0.0f };

std::string P2VE2Txt = "P2VE2";
Vector2D P2VE2Button_Position = { 25.0f, 0.0f };

std::string PVE2Txt = "PVE2";
Vector2D PVE2Button_Position = { 50.0f, 0.0f };

std::string PVPTxt = "PVP";
Vector2D PVPButton_Position = { -50.0f, -7.5f };

std::string P2VPTxt = "P2VP";
Vector2D P2VPButton_Position = { -25.0f, -7.5f };

std::string P2VP2Txt = "P2VP2";
Vector2D P2VP2Button_Position = { 25.0f, -7.5f };


