#include <iostream>
#include <ctime>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

/*This function handles the players hand, it will randomly generate 2 cards then ask
 * the player if they wish to draw more cards, the function will end when the player
 * does not want more cards or their hand is over 21 in total */
int playerHand (int min, int max) {
    srand(time(nullptr) * getpid());
    int total = 0;
    int lol;
    int ace = 0;
    int input = 0;
    printf("Your hand: ");
    printf("\n");
    for (int i = 0; i < 2; i++) {
        lol = rand() % (min + max) + 1;
        if(lol == 11) {
            printf("You got a ACE, what value should the ACE have (1) or (11): \n");
            scanf("%d", &ace);
            printf("\n");
            if (ace == 1) {
                lol = 1;
                printf("%d  ", lol);
                total += lol;
            } else if (ace == 11) {
                lol = 11;
                printf("%d  ", lol);
                total += lol;
            } else {
                printf("INVALID");
                printf("\n");
                while(true) {
                    printf("You got a ACE, what value should the ACE have (1) or (11):\n");
                    scanf("%d", &ace);
                    printf("\n");
                    if (ace == 1) {
                        lol = 1;
                        total += lol;
                        printf("%d  ", lol);
                        break;
                    } else if (ace == 11) {
                        lol = 11;
                        total += lol;
                        printf("%d  ", lol);
                        break;
                    } else {
                        printf("INVALID");
                    }
                }
            }
        }
        else {
            printf("%d  ", lol);
            total += lol;
        }
    }
    printf("= %d", total);
    printf("\n");
    printf("STAY(1) or HIT(2):\n");
    scanf("%d", &input);
    int hit = 0;
    while (input == 2) {
        printf("Your hand: ");
        printf("\n");
        printf("%d  ", total);
        hit = rand() % (1 + 9) + 1;
        printf("%d  ", hit);
        total += hit;
        printf("= %d", total);
        printf("\n");
        printf("STAY(1) or HIT(2):\n");
        scanf("%d", &input);
        if(total > 21){
            break;
        }
    }
    printf("Your hand: ");
    printf("= %d", total);
    printf("\n\n");
return total;
}

/* This function handles the dealers hand, it will generate 2 cards and will keep
 * drawing more cards if the dealer's hand is under 17 and ending when the dealers hand
 * total is over 17 */

int dealerHand (int min, int max) {
    srand(time(nullptr) * getpid());
    int lol2;
    int loop = 0;
    int total2 = 0;
    printf("Dealers hand: \n");
    for (int j = 0; j < 4; j++) {
        if(j >= 2) {
            lol2 = rand() % (min + max) + 1;
            printf("%d  ", lol2);
            total2 += lol2;
        }
        else{
            lol2 = rand() % (min + max) + 1;
        }
    }
        printf("= %d\n", total2);
     if (total2 < 17){
        printf("\nDealers hand is under 17, The Dealer will now draw more cards");
        printf("\n");
        printf("(%d) ", total2);
        loop++;
    }
    int hits;
    while(total2 < 17){
        hits = rand() % (1 + 9) + 1;
        printf("%d  ", hits);
        total2 += hits;
    }
    if (loop == 0) {
        printf("\n\n");
    }
    else if(loop > 0){

        printf("= %d\n\n", total2);
    }
    return total2;
}

/*The main handles the calculation who wins and losses as well as how much the player
 * wins or losses, the player will be asked for their bet, the bet will be taken from
 * the money the player has, if the player losses the bet, they lose the money, if they win
 * they make back double their bet (double and a half if they get blackjack), they player
 * wins and losses nothing if they and the dealer tie. the player will be asked if they want
 * to play again once their bet has either won or lost, they will be kicked out of the game and
 * not be asked to play again if they run out of money to bet, the minimum bet is $50, so if the
 * player money is below 50 they will be kicked out*/
int main() {
    int input;
    int money = 1000;
    int bet = 0;
    srand ( time(nullptr) *getpid() );
    while(true) {
        while(true) {
            printf("Credit: $%d\n", money);
            printf("How much would you like to bet (minimum bet is $50)\n$ ");
            scanf("%d", &bet);
            if(bet >= 50 && bet <= money){
                money -= bet;
                break;
            }
            else if (bet < 50){
                printf("INVALID, BET MUST BE AT LEAST $50\n");
            }
            else{
                printf("INVALID, BET CAN NOT EXCEED YOUR TOTAL CREDITS\n");
            }
        }
        int player = playerHand(1, 10);
        int dealer = dealerHand(1, 10);
        printf("---------Final Showdown---------\n");
        printf("Player hand: %d\n", player);
        printf("Dealer hand: %d\n", dealer);
         if (player == 21 && dealer == 21){
            printf("DRAW\n");
            money +=  bet;
        }
         else if (player == 21) {
            printf("BLACKJACK, YOU WIN!!!\n");
            money += bet * 2.5;
        }
         else if (dealer == 21){
            printf("DEALER GOT BLACKJACK, YOU LOSE\n");
        }
         else if (player > 21 && dealer > 21) {
            printf("YOU LOSE\n");
        }
         else if (dealer > 21) {
            printf("DEALER BUST, YOU WIN\n");
             money += bet * 2;
        }
         else if (player > 21) {
            printf("PLAYER BUST, YOU LOSE\n");
        }
         else if(player == dealer && dealer == player){
            printf("DRAW\n");
            money += bet;
        }
         else if (player > dealer) {
            printf("YOU WIN\n");
             money += bet * 2;
        }
         else if (player < dealer) {
            printf("YOU LOSE\n");
        }
        if(money <= 50){
            printf("\nYou dont have enough money to bet, goodbye");
            break;
        }
        else {
            printf("Credit: $%d\n", money);
            while(true) {
                printf("Would you like to play again? YES(1) NO(2)\n");
                scanf("%d", &input);

                if (input == 1) {
                    printf("\nNow dealing new hand...\n");
                    break;

                } else if (input == 2) {
                    break;

                } else{
                    printf("INVALID, INPUT 1 AND 2 ONLY\n");
                }
            }
            if (input == 2) {
                printf("\nGOODBYE!");
                break;
            }
        }
    }
    return 0;
}
