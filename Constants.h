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

const int ALL_ENTITIES_COUNT = 2;
const int PLAYER_INDEX = 0;
const int BLINKY_INDEX = 1;

const int FRIGHTENED_TIMER = 10;

const int MOVEMENTS_COUNT = 4;
const char MOVEMENT_LEFT = 'A';
const char MOVEMENT_RIGHT = 'D';
const char MOVEMENT_UP = 'W';
const char MOVEMENT_DOWN = 'S';
const char MOVEMENTS[] = { MOVEMENT_UP, MOVEMENT_LEFT, MOVEMENT_DOWN, MOVEMENT_RIGHT };
const char ESC_CHAR = 27;