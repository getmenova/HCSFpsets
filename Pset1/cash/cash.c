// how much change , minimum number of coins
//How to eat an elephant? One chunk at a time - refactored using modulo
#include < stdio.h >

  int main(void) {
    float dollars;
    do {
      dollars = get_float("Change: ");
    }
    while (dollars < 0);

    int cents = round(dollars * 100);

    int coins = 0;
//quarters
    coins += cents / 25;

    cents = cents % 25;
//dimes
    coins += cents / 10;
    cents = cents % 10;
//nickels
    coins += cents / 5;
    cents = cents % 5;
//pennies
    coins += cents;

    printf("%i\n", coins);