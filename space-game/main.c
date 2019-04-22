#include <gb/gb.h>
#include <stdio.h>

GameCharacter ship;
GameCharacter bug;
UBYTE spriteSize = 8;


void performantDelay(UINT8 numLoops) {
    UINT8 i;
    for (i = 0; i < numLoops; i++) {
       wait_vbl_done();
    }
}

void main() {

    DISPLAY_ON;
    SHOW_SPRITES;

    while(TRUE) {

    }

    printf("\n \n \n \n \n \n \n *** Game  Over ***");

}
