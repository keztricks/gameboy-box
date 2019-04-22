#include <gb/gb.h>

void performantDelay(UINT8 numLoops) {
    UINT8 i;
    for (i = 0; i < numLoops; i++) {
       wait_vbl_done();
    }
}
