/*Josh Langowitz
Software Systems
HW 1
Spring 2014
Cards exercise from Head First C*/

#include <stdio.h>
#include <stdlib.h>

/* Globals*/
char card_name[3];
int count = 0;

void get_card_name(){
    /* Prompts for user input of a card name and returns that name*/
    puts("Enter the card_name: ");
    scanf("%2s", card_name);
}

int get_card_val(char *card_name){
    /*Gets the value of a card name
    Returns 10 for a face card, 1 for an ace, 0 for 'X' to end the program.
    For other values, returns the atoi of that value.*/
    switch(card_name[0]){
    case 'K':
    case 'Q':
    case 'J':
        return 10;
    case 'A':
        return 1;
    case 'X':
        return 0;
    default:
        return atoi(card_name);
    }
}

void update_count(int val){
    /*Takes the inputted card value and updates the card count accordingly
    Values from 2-7 increment the count, values of 10 decrement it*/
    if ((val > 1) && (val < 8)){
        count++;
    } else if (val == 10){
        count--;
    }
    printf("Current count: %i\n", count);
}

int main(){
    /*Gets card inputs and updates the count until X is entered*/
    int val;
    while(1){
        get_card_name();
        val = get_card_val(card_name);
        if(!val){
            break;
        }
        if ((val < 1) || (val > 10)){
            puts("I don't understand that value!");
            continue;
        }
        update_count(val);
    }
    return 0;
}
