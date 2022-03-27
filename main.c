#include "rubiks.h"
#include "conio.h"
int main(void)
{
    T_COLOR couleur=B;
    int x,face=-1,sens,i;
    //printf("%d",(int)couleur);
    //display_rubiks(fill_rubiks(init_rubiks(create_rubiks())));
    //display_rubiks(blank_rubiks(init_rubiks(create_rubiks())));
    //display_rubiks(fill_rubiks(create_rubiks()));

    Face* rubiks = init_rubiks(create_rubiks());
    //change2(rubiks);
    interface();
    //scramble_rubiks(rubiks);

    //move_rubiks(rubiks);
    printf("\n\n");
    //croix_parfaite_UP(rubiks);
    /*blank_rubiks(rubiks);
    test_barre(rubiks);
    display_rubiks(rubiks);
    printf("\n\n");
    croix_jaune(rubiks);
    display_rubiks(rubiks);*/

    /*
    test_coin(rubiks);
    display_rubiks(rubiks);
    bienplacerlescoins(rubiks);
    printf("\n\n");
    display_rubiks(rubiks);*/
    //move_rubiks(rubiks);
    return 0;
}