#include <stdio.h>
#include <stdlib.h>

int lock = 1;
int items = 0;
int spaces = 10, counter = 0;

void producer() {
    --lock;
    ++items;
    --spaces;
    counter++;
    printf("Produced item id %d", counter);
    ++lock;
}

void consumer() {
    --lock;
    --items;
    ++spaces;
    printf("consumed item id %d", counter);
    counter--;
    ++lock;
}

int main() {
    char s;
    int choice, i;

    for (i = 1; i > 0; i++) {
        printf("\nYour role:");
        scanf(" %c", &s);
        if(s=='p'){
            choice = 1;
        }
        else if(s=='c'){
            choice = 2;
        }
        else if(s=='e') choice = 3;

        switch (choice) {
        case 1:
            if ((lock == 1) && (spaces != 0)) {
                producer();
            }
            else {
                printf("Buffer is full!");
            }
            break;

        case 2:
            if ((lock == 1) && (items != 0)) {
                consumer();
            }
            else {
                printf("Buffer is empty!");
            }
            break;

        case 3:
            exit(0);
            break;
        }
    }

    return 0;
}
