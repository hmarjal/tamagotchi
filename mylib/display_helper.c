/*
 * Heikki Marjala 2649304
 */

#include <inttypes.h>
#include <string.h>		// memset, strncpy
#include "display_helper.h"

void writeRow(struct displayText *dt_st, uint8_t row_n, const char *text)
{
	strncpy(dt_st->row[row_n], text, ROW_LEN);
}

void updateMenu(struct displayText *dt_st, uint8_t new)
{
		// Clear arrow from current position
		// 
		uint8_t i;
		for(i = 3; i < 8; i++)
		{
			memset(&dt_st->row[i][0], ' ', 1);
			memset(&dt_st->row[i][1], ' ', 1);
			memset(&dt_st->row[i][2], ' ', 1);
		}
		// Set arrow to new position
		memset(&dt_st->row[new%12][0], '-', 1);
		memset(&dt_st->row[new%12][1], '>', 1);
		memset(&dt_st->row[new%12][2], ' ', 1);
}

struct displayText createMainMenu(void)
{
	struct displayText menuText;
	writeRow(&menuText, 0,  "           enter");
	writeRow(&menuText, 1,  "                ");
	writeRow(&menuText, 2,  "                ");
	writeRow(&menuText, 3,  "-> Start Game   ");
	writeRow(&menuText, 4,  "   Check Status ");
	writeRow(&menuText, 5,  "   Test Sensors ");
	writeRow(&menuText, 6,  "   Help         ");
	writeRow(&menuText, 7,  "   Shut Down    ");
	writeRow(&menuText, 8,  "                ");
	writeRow(&menuText, 9,  "                ");
	writeRow(&menuText, 10, "                ");
	writeRow(&menuText, 11, "            next");
	return menuText;
}

struct displayText createGameMenu(void)
{
	struct displayText menuText;
	writeRow(&menuText, 0,  "|==========|exit");
	writeRow(&menuText, 1,  "|--------------|");
	writeRow(&menuText, 2,  "|              |");
	writeRow(&menuText, 3,  "|              |");
	writeRow(&menuText, 4,  "|              |");
	writeRow(&menuText, 5,  "|              |");
	writeRow(&menuText, 6,  "|              |");
	writeRow(&menuText, 7,  "|              |");
	writeRow(&menuText, 8,  "|              |");
	writeRow(&menuText, 9,  "|              |");
	writeRow(&menuText, 10, "|--------------|");
	writeRow(&menuText, 11, "|=========|start");
	return menuText;
}

struct displayText createWinMenu(void)
{
	struct displayText menuText;
	writeRow(&menuText, 0,  "|====|play again");
	writeRow(&menuText, 1,  "|--------------|");
	writeRow(&menuText, 2,  "| MONSTER      |");
	writeRow(&menuText, 3,  "|    DEFEATED! |");
	writeRow(&menuText, 4,  "| YOU WON      |");
	writeRow(&menuText, 5,  "|    THE GAME  |");
	writeRow(&menuText, 6,  "|YOUR TIME WAS |");
	writeRow(&menuText, 7,  "|              |");
	writeRow(&menuText, 8,  "|              |");
	writeRow(&menuText, 9,  "|              |");
	writeRow(&menuText, 10, "|--------------|");
	writeRow(&menuText, 11, "|=====|main menu");
	return menuText;	
}

struct displayText createLostMenu(void)
{
	struct displayText menuText;
	writeRow(&menuText, 0,  "|====|play again");
	writeRow(&menuText, 1,  "|--------------|");
	writeRow(&menuText, 2,  "| YOU LOST     |");
	writeRow(&menuText, 3,  "|    THE GAME  |");
	writeRow(&menuText, 4,  "|              |");
	writeRow(&menuText, 5,  "|              |");
	writeRow(&menuText, 6,  "|              |");
	writeRow(&menuText, 7,  "|              |");
	writeRow(&menuText, 8,  "|              |");
	writeRow(&menuText, 9,  "|              |");
	writeRow(&menuText, 10, "|--------------|");
	writeRow(&menuText, 11, "|=====|main menu");
	return menuText;
}
