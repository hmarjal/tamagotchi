/*
 * Heikki Marjala 2649304
 */

#include <inttypes.h>
#define ROW_LEN 17

struct displayText
{
	char row[12][ROW_LEN];
    char* row_ptr;
};

void writeRow(struct displayText *dt_st, uint8_t row_n, const char *text);
void updateMenu(struct displayText *dt_st, uint8_t new);
struct displayText createMainMenu(void);
struct displayText createGameMenu(void);
struct displayText createWinMenu(void);
struct displayText createLostMenu(void);
void gameMenu(struct displayText *dt_st);

