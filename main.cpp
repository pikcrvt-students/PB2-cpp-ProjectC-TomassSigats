#include <iostream>
#include <conio.h>
#include <unistd.h>
#include <math.h>

int main(){


#define KEY_UP 119 //    w      72 arrow up
#define KEY_DOWN 115 //  s      80 arrow down
#define KEY_LEFT 97 //   a      75 arrow left
#define KEY_RIGHT 100 // d      77 arrow right
#define KEY_ACT 32  //   space
#define KEY_F 102 //     f      27 esc


    int mapsize_x = 50 + 2;
    int mapsize_y = 10 + 2;
    char map[mapsize_x][mapsize_y];

    for (int yi = 0; yi < mapsize_y; yi++){
        for (int xi = 0; xi < mapsize_x; xi++) {
            if (yi == 0){
                if (xi == 0){
                    map[xi][yi] = '_';
                }
                else if (xi == mapsize_x-1){
                    map[xi][yi] = '_';
                }
                else {
                    map[xi][yi] = '_';
                }
            }
            else if (yi == mapsize_y-1){
                if (xi == 0){
                    map[xi][yi] = '|';
                }
                else if (xi == mapsize_x-1){
                    map[xi][yi] = '|';
                }
                else {
                    map[xi][yi] = '_';
                }
            }
            else if (xi == mapsize_x-1 or xi == 0){
                map[xi][yi] = '|';
            }
            else {
                map[xi][yi] = '.';
            }
        }
    }           //creating map

    int playercoord_x, playercoord_y;                     // assigning player start pos
    playercoord_x = mapsize_x / 2;
    playercoord_y = mapsize_y / 2;
    map[playercoord_x][playercoord_y] = '@';


    for (int yi = 0; yi < mapsize_y; yi++) {
        for (int xi = 0; xi < mapsize_x; xi++) {
            std::cout << map[xi][yi];
        }
        std::cout << std::endl;
    }               //map first output

    std::cout << std::endl;
    std::cout << "\tYou have mined: 0 coins" << std::endl;
    for (int i = 0; i < 100; i++){std::cout << '_';}
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\tMovement:  W\t\t   Mine: SPACE" << std::endl;
    std::cout << "\t         A S D" << std::endl;
    std::cout << "\t\t\t\t   Finish mining: F" << std::endl;


    bool crypto = false;
    bool virus = false;
    bool escape = false;
    bool stalemate = false;
    int luck;
    int crypto_count = 0;


    while (true) {

        if (map[playercoord_x][playercoord_y] == '@'){
            map[playercoord_x][playercoord_y] = '.';
        }

        switch(getch()) {

            case KEY_UP:
                if (playercoord_y - 1 == 0 or map[playercoord_x][playercoord_y - 1] == 'C'){
                    break;
                }
                else {
                    --playercoord_y;
                    break;
                }
            case KEY_DOWN:
                if (playercoord_y + 2 == mapsize_y or map[playercoord_x][playercoord_y + 1] == 'C'){
                    break;
                }
                else {
                    ++playercoord_y;
                    break;
                }
            case KEY_LEFT:
                if (playercoord_x - 1 == 0 or map[playercoord_x - 1][playercoord_y] == 'C') {
                    break;
                }
                else {
                    --playercoord_x;
                    break;
                }
            case KEY_RIGHT:
                if (playercoord_x + 2 == mapsize_x or map[playercoord_x + 1][playercoord_y] == 'C') {
                    break;
                }
                else {
                    ++playercoord_x;
                    break;
                }
            case KEY_ACT:
                luck = rand() % 250;
                if (luck < 50 and map[playercoord_x][playercoord_y] != 'C') {   // 20 % chance of coin
                    crypto = true;
                }
                else if (50 <= luck and luck < 55 and map[playercoord_x][playercoord_y] != 'C') { // 2% chance of virus
                    virus = true;
                }
                break;
            case KEY_F:
                escape = true;
                break;

        }



        if (map[playercoord_x][playercoord_y] != 'C') {
            map[playercoord_x][playercoord_y] = '@';
        }                    // replace players trail
        if (escape){
            system("cls");
            break;

        }
        if (crypto){
            map[playercoord_x][playercoord_y] = 'C';
            ++crypto_count;
            crypto = false;
        }
        if (virus){
            system("cls");
            break;
        }
        if (map[playercoord_x + 1][playercoord_y] != '.'){
            if (map[playercoord_x - 1][playercoord_y] != '.'){
                if (map[playercoord_x][playercoord_y + 1] != '.'){
                    if (map[playercoord_x][playercoord_y - 1] != '.'){
                        if (map[playercoord_x][playercoord_y] == 'C'){
                            stalemate = true;
                            system("cls");
                            break;
                        }
                    }
                }
            }
        }               // stalemate




        system("cls");

        for (int yi = 0; yi < mapsize_y; yi++) {
            for (int xi = 0; xi < mapsize_x; xi++) {
                std::cout << map[xi][yi];
            }
            std::cout << std::endl;
        }                   //map output

        std::cout << std::endl;
        std::cout << "\tYou have mined: " << crypto_count << " coins" << std::endl;
        for (int i = 0; i < 100; i++){std::cout << '_';}
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "\tMovement:  W\t\t   Mine: SPACE" << std::endl;
        std::cout << "\t         A S D" << std::endl;
        std::cout << "\t\t\t\t   Finish mining: F" << std::endl;

    }               // game loop


    if (escape){
        for (int yi = 0; yi < mapsize_y; yi++) {
            for (int xi = 0; xi < mapsize_x; xi++) {
                std::cout << map[xi][yi];
            }
            std::cout << std::endl;
        }                   //map output

        std::cout << std::endl;
        std::cout << "\tYou have mined: " << crypto_count << " coins" << std::endl;
        for (int i = 0; i < 100; i++){std::cout << '_';}
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "\tYou decided that " << crypto_count << " coins is enough..."<< std::endl;
        std::cout << std::endl;
        if (crypto_count == 0){
            std::cout << "\tDid you even try?";
        }
        else if (crypto_count < 10){
            std::cout << "\t-_- Zzz...";
        }
        else if (crypto_count < 20){
            std::cout << "\tI'm impressed!";
        }
        else if (crypto_count < 30){
            std::cout << "\tSo this is your limit?";
        }
        else if (crypto_count < 40){
            std::cout << "\t(O_O) e?";
        }
        else if (crypto_count < 50){
            std::cout << "\tWeren't you gonna go for 50?";
        }
        else if (crypto_count == 50){
            std::cout << "\tHaha, exactly 50";
        }
        else if (crypto_count == 69){
            std::cout << "\tYou wanna play? Let's play!";
        }
        else if (400 > crypto_count and crypto_count > 50){
            std::cout << "\tArE yoU SeRiOuS riGHt nEoW? ";
        }
        else if (crypto_count == 420){
            std::cout << "\tThat's it, I'm calling Snoop Dogg...";
        }
        else if (crypto_count == 499){
            std::cout << "\tMy sincerest congratulations... You've reached max score! :)";
        }
        else {
            std::cout << "\tLucky I guess...";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        sleep(5);
        system("pause");
    }

    else if (stalemate){
        for (int yi = 0; yi < mapsize_y; yi++) {
            for (int xi = 0; xi < mapsize_x; xi++) {
                std::cout << map[xi][yi];
            }
            std::cout << std::endl;
        }                   //map output

        std::cout << std::endl;
        std::cout << "\tYou have mined: " << crypto_count << " coins" << std::endl;
        for (int i = 0; i < 100; i++){std::cout << '_';}
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "\tAlthough this is not chess, somehow you ended up in stalemate...";
        std::cout << std::endl;
        std::cout << std::endl;
        sleep(5);
        system("pause");
    }

    else if (virus) {
        map[playercoord_x][playercoord_y] = 'V';
        for (int yi = 0; yi < mapsize_y; yi++) {
            for (int xi = 0; xi < mapsize_x; xi++) {
                std::cout << map[xi][yi];
            }
            std::cout << std::endl;
        }                   //map output
        sleep(2);
        system("cls");
        std::cout << "\n\n\n\n\n\n\n\tYou have caught virus :DD:DDDDD:D:D:D::DD:DD:D:DDD";
        sleep(1);
        system("cls");
        int randint = rand() % 100 + 3;
        while (true) {
            randint = randint * randint * randint;
            std::cout << randint;
        }
    }
return 0;
}