#pragma once

const int DEFAULT_CONSOLE_COLOUR = 15; //White

const char MAP_FILE_NAME[] = "map.txt";

const char WALL_CHARACTER = '#';
const char POINT_CHARACTER = '-';
const char ENERGIZER_CHARACTER = '@';
const char BLANK = ' ';

const int PLAYER_COLOUR = 6; //Yellow
const char PLAYER_SYMBOL = 'C';

const int BLINKY_COLOUR = 4; //Red
const char BLINKY_SYMBOL = 'B';

const int PINKY_COLOUR = 12; //Pink
const char PINKY_SYMBOL = 'P';

const int INKY_COLOUR = 1; //Blue
const char INKY_SYMBOL = 'I';

const int CLYDE_COLOUR = 2; //Green
const char CLYDE_SYMBOL = 'Y';
const double CLYDE_DISTANCE = 8.0;
const double EPSILON = 1e-5;

const int ALL_ENTITIES_COUNT = 5;
const int PLAYER_INDEX = 0;
const int BLINKY_INDEX = 1;
const int PINKY_INDEX = 2;
const int INKY_INDEX = 3;
const int CLYDE_INDEX = 4;

const int FRIGHTENED_TIMER = 10;

const int MOVEMENTS_COUNT = 4;
const char MOVEMENT_LEFT = 'A';
const char MOVEMENT_RIGHT = 'D';
const char MOVEMENT_UP = 'W';
const char MOVEMENT_DOWN = 'S';
const char MOVEMENTS[] = { MOVEMENT_UP, MOVEMENT_LEFT, MOVEMENT_DOWN, MOVEMENT_RIGHT };
const char ESC_CHAR = 27;