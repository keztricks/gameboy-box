#include <gb/gb.h>
#include <stdio.h>
#include "utils.c"
#include "GameCharacter.c"
#include "../assets/shipBug-sprite.c"

GameCharacter ship;
GameCharacter bug;
UBYTE spriteSize = 8;
UINT8 enemyBaseSpeed = 5;
UINT8 enemySpeedIncrease = 1;
UINT8 enemySpeed;

void moveGameCharacter(GameCharacter* character, UINT8 x, UINT8 y) {  // * is pass by ref/pointer
    move_sprite(character->spriteIDs[0], x, y);
    move_sprite(character->spriteIDs[1], x + spriteSize, y);
    move_sprite(character->spriteIDs[2], x, y + spriteSize);
    move_sprite(character->spriteIDs[3], x + spriteSize, y + spriteSize);
}

void setupShip() {
    ship.x = 80;
    ship.y = 130;
    ship.width = 16;
    ship.height = 16;

    set_sprite_tile(0, 0);
    ship.spriteIDs[0] = 0;
    set_sprite_tile(1, 2);
    ship.spriteIDs[1] = 1;
    set_sprite_tile(2, 1);
    ship.spriteIDs[2] = 2;
    set_sprite_tile(3, 3);
    ship.spriteIDs[3] = 3;

    moveGameCharacter(&ship, ship.x, ship.y);
}

void setupBug(){
    bug.x = 30;
    bug.y = 0;
    bug.width = 16;
    bug.height = 16;    

    // load sprites for bug
    set_sprite_tile(4, 4);
    bug.spriteIDs[0] = 4;
    set_sprite_tile(5, 6);
    bug.spriteIDs[1] = 5;
    set_sprite_tile(6, 5);
    bug.spriteIDs[2] = 6;
    set_sprite_tile(7, 7);
    bug.spriteIDs[3] = 7;

    moveGameCharacter(&bug, bug.x, bug.y);
}

void movePlayer() {
    if(ship.x > 8){
        if(joypad() & J_LEFT){
            ship.x -= 2;
            moveGameCharacter(&ship, ship.x, ship.y);
        }
    }
    if(ship.x + ship.width <= 166){
        if(joypad() & J_RIGHT){
            ship.x += 2;
            moveGameCharacter(&ship, ship.x, ship.y);
        }
    }
}

void moveEnemy() {
        bug.y += enemySpeed;
        moveGameCharacter(&bug, bug.x, bug.y);

        if(bug.y >= 144){
            bug.y=0;
            bug.x = ship.x;
            enemySpeed += enemySpeedIncrease;
        }
}

UBYTE checkCollision(GameCharacter* firstCharacter, GameCharacter* secondCharacter) {
    return (firstCharacter->x + 1 >= secondCharacter->x + 1 && firstCharacter->x + 1 <= secondCharacter->x + secondCharacter->width - 1) && (firstCharacter->y + 1 >= secondCharacter->y + 1 && firstCharacter->y + 1 <= secondCharacter->y + 1 + secondCharacter->height - 1) || (secondCharacter->x + 1 >= firstCharacter->x + 1 && secondCharacter->x + 1 <= firstCharacter->x + 1 + firstCharacter->width - 1) && (secondCharacter->y + 1 >= firstCharacter->y + 1 && secondCharacter->y + 1 <= firstCharacter->y + 1 + firstCharacter->height - 1);
}

void playGame() {
    enemySpeed = enemyBaseSpeed;
    set_sprite_data(0, 8, shipBug);
    setupShip();
    setupBug();

    DISPLAY_ON;
    SHOW_SPRITES;

    while(TRUE) {
        movePlayer();
        moveEnemy();
        performantDelay(5);

        if (checkCollision(&ship, &bug)) {
            printf("\n \n \n \n \n \n");
            printf(" *** Game  Over ***\n \nHit Start to Restart\n \n \n \n \n \n \n \n \n \n");
            waitpad(J_START);
            printf("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n");
            playGame();
        }
    }
}
void main() {
    //BYTE runMain = 1;

    printf("\n \n \n \n \n \n \n*** Press  Start ***");
    waitpad(J_START);
    printf("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n");

    playGame();
}
