#include "rubiks.h"
#include "conio.h"

int select_color(T_COLOR color)
{
    return (int)color;
}

T_COLOR color_select(int color)
{
    if (color == 0)
        return R;
    else if (color == 1)
        return B;
    else if (color == 2)
        return G;
    else if (color == 3)
        return W;
    else if (color == 4)
        return Y;
    else if (color == 5)
        return O;
    else
        return LG;
}

char color_select_2(int color)
{
    if (color == 0)
    {
        c_textcolor(RED);
        return 'R';
    }
    else if (color == 1)
    {
        c_textcolor(BLUE);
        return 'B';
    }
    else if (color == 2)
    {
        c_textcolor(GREEN);
        return 'G';
    }
    else if (color == 3) {
        c_textcolor(WHITE);
        return 'W';
    }
    else if (color == 4)
    {
        c_textcolor(YELLOW);
        return 'Y';
    }
    else if (color == 5) {
        c_textcolor(ORANGE);
        return 'O';
    }
    else {
        c_textcolor(LIGHTGRAY);
        return '-';
    }
}


int side_to_index(T_SIDE side)
{
    if (side==LEFT)
        return 1;
    else if (side==FRONT)
        return 2;
    else if (side == RIGHT)
        return 3;
    else if (side == BACK)
        return 4;
    else if (side == UP)
        return 0;
    else if (side == DOWN)
        return 5;
    else
        return -1;
}
//LEFT = 1 -> Orange -> 5 (rang de la couleur pour déterminer la face)
//FRONT = 2 -> White -> 3
//RIGHT = 3 -> Red -> 0
//BACK = 4 -> Yellow -> 4
//UP = 0  -> Bleu -> 1
// DOWN = 5 -> Green -> 2

int rank_to_side(int rank)
{
    if (rank==5)
        return 1;
    else if (rank==3)
        return 2;
    else if (rank==0)
        return 3;
    else if (rank==4)
        return 4;
    else if (rank==1)
        return 0;
    else if (rank==2)
        return 5;
    else
        return -1;
}

T_SIDE index_to_side(int side)
{
    if (side==0)
        return UP;
    if (side==1)
        return LEFT;
    if (side == 2)
        return FRONT;
    if (side == 3)
        return RIGHT;
    if (side == 4)
        return BACK;
    if (side == 5)
        return DOWN;

}

Face* create_rubiks() {
    Face *rubiks = NULL;
    int i, j;
    rubiks = (Face *) malloc(6 * sizeof(Face));
    for (i=0;i<6;i++)
    {
        (rubiks+i)->Tab2D = (T_COLOR **) malloc(3 * sizeof(T_COLOR *));
    }
    for (i = 0; i < 6; i++) {
        for (j=0;j<3;j++) {
            (rubiks + i)->Tab2D[j] = (T_COLOR *) malloc(3 * sizeof(T_COLOR));
        }
    }

    return rubiks;
}


Face* init_rubiks(Face* rubiks) {
    int i, j, k,l;
    T_COLOR color=R;
    //(rubiks[0]).Tab2D[2][1] = O;
    //printf("%d\n", (int) ((rubiks[0]).Tab2D[2])[1]);

    for (i=0;i<6;i++)
    {
        rubiks[i].Nom_Face = index_to_side(i);
    }
    for (i = 0; i < 6; i++) {
        for (l=0;l<6;l++)
        {
            if (side_to_index(rubiks[l].Nom_Face) == rank_to_side(i))
            {
                break;
            }
        }
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                rubiks[l].Tab2D[j][k] = color;
            }
        }
        color = color_select(i+1) ;
    }
    //rubiks[5].Tab2D[2][1]=color_select(0);
    //rubiks[3].Tab2D[1][1]=color_select(1);
    //rubiks[0].Tab2D[0][1]=color_select(0);
    //rubiks[4].Tab2D[2][2]=color_select(5);
    //rubiks[1].Tab2D[0][0]=color_select(5);
    //rubiks[2].Tab2D[2][0]=color_select(3);
    return rubiks;
}

void display_rubiks(Face* rubiks)
{
    int i,j,k,l,Tab[6],cpt=0,c=0,kp=0;
    for (i=0;i<6;i++) //On va de 0 à 5 pour passer toutes les faces possibles dans l'ordre (dans index_to_side) UP->LEFT->FRONT->...
    {
        for (j=0;j<6;j++) //On passe dans chaque case du rubiks pour chercher à quelle rang se trouve la face recherchée. Pour i=0=UP on va chercher dans le rubiks où se trouve UP
        {
            if (index_to_side(i) == rubiks[j].Nom_Face) // On a trouvé le rang où se trouve la face (c'est le rang j)
            {
                break;  //On break pour pouvoir utiliser ce j
            }
        }
        Tab[i] = j;  //On met ce j (le rang où se trouve la face rechrechée) dans un tableau
    }

    //Maintenant, Tab a dedans les rangs dans l'ordre UP->LEFT->FRONT->...

    for (i=0; i<3; i++) //i=0, pour afficher UP, i=1 pour afficher LFRB, i=2 pour afficher DOWN, page 4 du poly pour comprendre
    {
        if (cpt==0 || cpt==5) //cpt =0 quand on veut afficher UP, cpt=5 quand on veut afficher DOWN
        {
            c=0; //c correspond à la colonne, on l'initialise à 0, normal
            for (l=0;l<3;l++)  //ça c pour afficher les 3 premieres lignes de UP, va voir la page 4 du poly, une boucle = une ligne
            {
                for (k=0;k<7;k++)
                {
                    printf(" "); //ça c juste pour faire les espaces pour UP et DOWN avant d'afficher, page 4 du poyly
                }
                for (k=0;k<3;k++)
                {
                    printf("%c ",color_select_2(rubiks[Tab[cpt]].Tab2D[c][k])); //Tab[cpt] : Pour Tab[0] t'as le rang où se trouve UP, pour Tab[1] le rang où se trouve LEFT,...
                    //On veut afficher le rubiks dans l'ordre des faces c pour ça que j'ai mis rubiks[Tab[cpt]], ensuite le .Tab2D[c][k] c pour les colonnes et les lignes
                }
                c++; //Augmenter d'une colonne
                printf("\n"); //Passer à la ligne à la fin de 3 mini cubes
            }
        }

        else  //On rentre dans la condition else, pour LEFT FRONT RIGHT BACK
        {
            for (l=0;l<3;l++) //Premiere boucle = Afficher premiere ligne de LEFT + premiere ligne de F + premiere ligne de R + premiere ligne de B, Deuxieme tour de boucle = Afficher deuxieme ligne de LEFT ...
            {
                for (k=0;k<12;k++) //12 parce que y a 12 mini cubes à afficher pour un tour de boucle de l (la boucle juste au dessus) 3 minicubes de la premiere ligne de L + 3 minicubes de la premiere ligne de F...
                {
                    printf("%c ",color_select_2(rubiks[Tab[cpt]].Tab2D[l][kp++])); //Afficher la couleur du minicube en passant par color_select_2 qui renvoie un char pour l'instant (on n'a pas encore use conio)
                    if (k==2 || k==5 || k==8) //ça c quand on passe de la ligne de LEFT à la ligne de Front, et de la ligne de Front à la ligne de Right...
                    {
                        kp =0; //kp c'est un petit k qui se réinitialise à chaque fois qu'on passe de la ligne de Left à la ligne de front vu qu'on le use dans Tab2D[l][kp++] au dessus, pour que quand on passe à la ligne d'après ça repasse à 0, qu'on affiche bien [0][0] de la ligne d'après (quand je dis ligne d'après c par exemple ligne Left -> ligne Front
                        printf(" "); //on aère un peu
                        cpt++; //oe
                    }
                }
                printf("\n"); //Saut de ligne pour passer de la premiere ligne de LFRB à la deuxieme ligne de LFRB
                cpt = 1; //Ah si c'est pour Tab[cpt] on va le remettre à 1 pour bien que dans rubiks[Tab[cpt]] on ait la face où y a Left quand cpt=1 (car quand on saute de ligne on repasse à Left)
                kp=0; //On remet kp à 0 pour le tour d'après
            }
            printf("\n"); //Saut de ligne pour passer à DOWN
            cpt = 5; //on passe à DOWN
        }

        if (i==0)
        {
            printf("\n"); //y avait pas besoin de ça
            cpt++;//pr passer de cpt=0 à cpt=1, pck dans i=0 cpt=0. Jreviens dans 15 min att 2 minatt un peu plus
        }



    }
}


Face* blank_rubiks(Face* rubiks)
{
    int i,j,k;
    init_rubiks(rubiks);
    for (k=0;k<6;k++)
    {
        for (i=0;i<3;i++)
        {
            for (j=0;j<3;j++)
            {
                rubiks[k].Tab2D[i][j] = color_select(-1);
            }
        }
    }
    return rubiks;
}

Box adjacent(Box Tab, int face, int coorx,int coory)
{
    if (face==0)
    {
        if (coorx==0 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=0;
            Tab.face=1;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=2;
            Tab.face2=4;
        }

        if (coorx==0 && coory==1)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=1;
            Tab.face=4;
            Tab.ver2=0;
        }

        if (coorx==0 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=2;
            Tab.face=3;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=0;
            Tab.face2=4;
        }

        if (coorx==1 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=1;
            Tab.face=1;
            Tab.ver2=0;
        }

        if (coorx==1 && coory==1)
        {
            Tab.ver=0;
            Tab.ver2=0;
        }

        if (coorx==1 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=1;
            Tab.face=3;
            Tab.ver2=0;
        }

        if (coorx==2 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=2;
            Tab.face=1;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=0;
            Tab.face2=2;
        }

        if (coorx==2 && coory==1)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=1;
            Tab.face=2;
            Tab.ver2=0;
        }

        if (coorx==2 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=2;
            Tab.face=2;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=0;
            Tab.face2=3;
        }
    }

    if (face==1)
    {
        if (coorx==0 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=0;
            Tab.face=0;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=2;
            Tab.face2=4;
        }

        if (coorx==0 && coory==1)
        {
            Tab.ver=1;
            Tab.coor[0] = 1;
            Tab.coor[1]=0;
            Tab.face=0;
            Tab.ver2=0;
        }

        if (coorx==0 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] = 2;
            Tab.coor[1]=0;
            Tab.face=0;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=0;
            Tab.face2=2;
        }

        if (coorx==1 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] = 1;
            Tab.coor[1]=2;
            Tab.face=4;
            Tab.ver2=0;
        }

        if (coorx==1 && coory==1)
        {
            Tab.ver=0;
            Tab.ver2=0;
        }

        if (coorx==1 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] = 1;
            Tab.coor[1]=0;
            Tab.face=2;
            Tab.ver2=0;
        }

        if (coorx==2 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] = 2;
            Tab.coor[1]=2;
            Tab.face=4;
            Tab.ver2=1;
            Tab.coor2[0]=2;
            Tab.coor2[1]=0;
            Tab.face2=5;
        }

        if (coorx==2 && coory==1)
        {
            Tab.ver=1;
            Tab.coor[0] = 1;
            Tab.coor[1]=0;
            Tab.face=5;
            Tab.ver2=0;
        }

        if (coorx==2 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] = 2;
            Tab.coor[1]=0;
            Tab.face=2;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=0;
            Tab.face2=5;
        }
    }

    if (face==2)
    {
        if (coorx==0 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] = 2;
            Tab.coor[1]=0;
            Tab.face=0;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=2;
            Tab.face2=1;
        }

        if (coorx==0 && coory==1)
        {
            Tab.ver=1;
            Tab.coor[0] = 2;
            Tab.coor[1]=1;
            Tab.face=0;
            Tab.ver2=0;
        }

        if (coorx==0 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] = 2;
            Tab.coor[1]=2;
            Tab.face=0;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=0;
            Tab.face2=3;
        }

        if (coorx==1 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] = 1;
            Tab.coor[1]=2;
            Tab.face=1;
            Tab.ver2=0;
        }

        if (coorx==1 && coory==1)
        {
            Tab.ver=0;
            Tab.ver2=0;
        }

        if (coorx==1 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] = 1;
            Tab.coor[1]=0;
            Tab.face=3;
            Tab.ver2=0;
        }

        if (coorx==2 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] = 2;
            Tab.coor[1]=2;
            Tab.face=1;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=0;
            Tab.face2=5;
        }

        if (coorx==2 && coory==1)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=1;
            Tab.face=5;
            Tab.ver2=0;
        }

        if (coorx==2 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] = 2;
            Tab.coor[1]=0;
            Tab.face=3;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=2;
            Tab.face2=5;
        }
    }

    if (face==3)
    {
        if (coorx==0 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] = 2;
            Tab.coor[1]=2;
            Tab.face=0;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=2;
            Tab.face2=2;
        }

        if (coorx==0 && coory==1)
        {
            Tab.ver=1;
            Tab.coor[0] = 1;
            Tab.coor[1]=2;
            Tab.face=0;
            Tab.ver2=0;
        }

        if (coorx==0 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=2;
            Tab.face=0;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=0;
            Tab.face2=4;
        }

        if (coorx==1 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] = 1;
            Tab.coor[1]=2;
            Tab.face=2;
            Tab.ver2=0;
        }

        if (coorx==1 && coory==1)
        {
            Tab.ver=0;
            Tab.ver2=0;
        }

        if (coorx==1 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] =1;
            Tab.coor[1]=0;
            Tab.face=4;
            Tab.ver2=0;
        }

        if (coorx==2 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] =2;
            Tab.coor[1]=2;
            Tab.face=2;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=2;
            Tab.face2=5;
        }

        if (coorx==2 && coory==1)
        {
            Tab.ver=1;
            Tab.coor[0] =1;
            Tab.coor[1]=2;
            Tab.face=5;
            Tab.ver2=0;
        }

        if (coorx==2 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] =2;
            Tab.coor[1]=0;
            Tab.face=4;
            Tab.ver2=1;
            Tab.coor2[0]=2;
            Tab.coor2[1]=2;
            Tab.face2=5;
        }
    }

    if (face==4)
    {
        if (coorx==0 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=2;
            Tab.face=0;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=2;
            Tab.face2=3;
        }

        if (coorx==0 && coory==1)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=1;
            Tab.face=0;
            Tab.ver2=0;
        }

        if (coorx==0 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] = 0;
            Tab.coor[1]=0;
            Tab.face=0;
            Tab.ver2=1;
            Tab.coor2[0]=0;
            Tab.coor2[1]=0;
            Tab.face2=1;
        }

        if (coorx==1 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] =1;
            Tab.coor[1]=2;
            Tab.face=3;
            Tab.ver2=0;
        }

        if (coorx==1 && coory==1)
        {
            Tab.ver=0;
            Tab.ver2=0;
        }

        if (coorx==1 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] =1;
            Tab.coor[1]=0;
            Tab.face=1;
            Tab.ver2=0;
        }

        if (coorx==2 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] =2;
            Tab.coor[1]=2;
            Tab.face=3;
            Tab.ver2=1;
            Tab.coor2[0]=2;
            Tab.coor2[1]=2;
            Tab.face2=5;
        }

        if (coorx==2 && coory==1)
        {
            Tab.ver=1;
            Tab.coor[0] =2;
            Tab.coor[1]=1;
            Tab.face=5;
            Tab.ver2=0;
        }

        if (coorx==2 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] =2;
            Tab.coor[1]=0;
            Tab.face=1;
            Tab.ver2=1;
            Tab.coor2[0]=2;
            Tab.coor2[1]=0;
            Tab.face2=5;
        }
    }

    if (face==5)
    {
        if (coorx==0 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] =2;
            Tab.coor[1]=2;
            Tab.face=1;
            Tab.ver2=1;
            Tab.coor2[0]=2;
            Tab.coor2[1]=0;
            Tab.face2=2;
        }

        if (coorx==0 && coory==1)
        {
            Tab.ver=1;
            Tab.coor[0] = 2;
            Tab.coor[1]=1;
            Tab.face=2;
            Tab.ver2=0;
        }

        if (coorx==0 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] =2;
            Tab.coor[1]=2;
            Tab.face=2;
            Tab.ver2=1;
            Tab.coor2[0]=2;
            Tab.coor2[1]=0;
            Tab.face2=3;
        }

        if (coorx==1 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] =2;
            Tab.coor[1]=1;
            Tab.face=1;
            Tab.ver2=0;
        }

        if (coorx==1 && coory==1)
        {
            Tab.ver=0;
            Tab.ver2=0;
        }

        if (coorx==1 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] =2;
            Tab.coor[1]=1;
            Tab.face=3;
            Tab.ver2=0;
        }

        if (coorx==2 && coory==0)
        {
            Tab.ver=1;
            Tab.coor[0] =2;
            Tab.coor[1]=0;
            Tab.face=1;
            Tab.ver2=1;
            Tab.coor2[0]=2;
            Tab.coor2[1]=2;
            Tab.face2=4;
        }

        if (coorx==2 && coory==1)
        {
            Tab.ver=1;
            Tab.coor[0] =2;
            Tab.coor[1]=1;
            Tab.face=4;
            Tab.ver2=0;
        }

        if (coorx==2 && coory==2)
        {
            Tab.ver=1;
            Tab.coor[0] =2;
            Tab.coor[1]=2;
            Tab.face=3;
            Tab.ver2=1;
            Tab.coor2[0]=2;
            Tab.coor2[1]=0;
            Tab.face2=4;
        }
    }

    return Tab;
}



Face* fill_rubiks(Face* rubiks)
{
    int i,j,k,l,m,n,col,coorx,coory,face,versame=0,colver=0,ver32=0,cptadj=0,ver3=0,v,cptadj2=0,verpos=0,verla=0,Fac[6],tf=0,verf=0,vercol=0,verjsp=0,verjsp2=0,Garde[6];
    Box Tab;
    Col Coul[6];
    for (i=0;i<6;i++)
    {
        for (j=0;j<6;j++)
        {
            Coul[i].cpt[j] = 0;
        }
        Coul[i].Centre = 0;
        Coul[i].Sommet = 0;
        Coul[i].Arete = 0;
        Coul[i].nbocc = 0;
    }
    blank_rubiks(init_rubiks(rubiks));
    for (i=0;i<6;i++) {
        do {
            printf("0 : UP    1 : LEFT    2 : FRONT   3 : RIGHT   4 : BACK    5 : DOWN\nChoose the side :");
            scanf("%d",&face);
            printf("\n");
            verf=0;
            for (n=0;n<tf;n++)
            {
                if (Fac[n]==face)
                {
                    verf=-1;
                }
            }

            if (verf!=0)
            {
                printf("YOU HAVE ALREADY FILLED THIS SIDE!!\n");
            }

            Fac[tf++]=face;
        }while(verf!=0);
        for (j=0;j<3;j++)
        {
            for (k=0;k<3;k++) {
                do {
                    verjsp=0;
                    verjsp2=0;
                    display_rubiks(rubiks);
                    printf("\n");
                    if (versame==0 && ver3!=-1 && ver32!=-1 && verpos==0 && verla==0 && vercol==0)
                    {printf("NEW BOX :\n");}
                    if (versame==1)
                    {
                        printf("SAME COLOR CANT BE ON ADJACENT SIDES!! \n");
                        versame=0;
                    }
                    if (verla==-1)
                    {
                        printf("THIS BOX IS TAKEN!!\n");
                        verla=0;
                    }

                    if (vercol==-1)
                    {
                        printf("THIS COLOR CANT APPEAR MORE THAN 9 TIMES!! \n");
                        vercol = 0;
                    }

                    if (ver3==-1 || ver32==-1)
                    {
                        printf("THERE CANT BE MORE THAN 3 TIMES THE SAME ADJACENT COLOR!!\n");
                        ver3=0;
                        ver32=0;
                    }

                    if (verpos==-1)
                    {
                        printf("THAT COLOR CANT BE ON MORE THAN 1 CENTER!!\n");
                        verpos=0;
                    }
                    if (verpos==-2)
                    {
                        printf("THAT COLOR CANT BE ON MORE THAN 4 EDGES!!\n");
                        verpos=0;
                    }
                    if (verpos==-3)
                    {
                        printf("THAT COLOR CANT BE ON MORE THAN 4 VERTEX!!\n");
                        verpos=0;
                    }
                    printf("Choose the line  :");
                    scanf("%d", &coorx);
                    printf("Choose the column :");
                    scanf("%d", &coory);
                    printf("0 : RED    1 : BLUE    2 : GREEN   3 : WHITE   4 : YELLOW    5 : ORANGE\nChoose a color :");
                    scanf("%d", &col);
                    printf("\n");

                    if (rubiks[face].Tab2D[coorx][coory]<6)
                    {
                        verla = -1;
                    }

                    if (coorx==1 && coory==1)
                    {
                        Coul[col].Centre++;
                        if (Coul[col].Centre>1)
                        {
                            verpos=-1;
                        }
                    }
                    else if ((coorx==0 && coory==0) || (coorx==0 && coory==2) || (coorx==2 && coory==0) || (coorx==2 && coory==2))
                    {
                        Coul[col].Sommet++;
                        if (Coul[col].Sommet>4)
                        {
                            verpos=-2;
                        }
                    }

                    else if ((coorx==0 && coory==1) || (coorx==1 && coory==0) || (coorx==1 && coory==2) || (coorx==2 && coory==1))
                    {
                        Coul[col].Arete++;
                        if (Coul[col].Arete>4)
                        {
                            verpos=-3;
                        }
                    }

                    Coul[col].nbocc++;
                    if (Coul[col].nbocc>9)
                    {
                        vercol = -1;
                    }

                    Tab = adjacent(Tab,face,coorx,coory);

                    if (verpos==0 && verla==0 && vercol==0)
                    {
                        if (Tab.ver==1)
                        {
                            if ((int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]] == (int)color_select(col))
                            {
                                versame=1;
                            }
                            if ((int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]]<6 && (int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]]>=0)
                            {
                                Coul[(int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]]].cpt[col]++;
                                Coul[col].cpt[(int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]]]++;
                                //printf("rentre");
                                verjsp=1;
                                //printf("%d",Coul[col].cpt[col]);
                                for (m=0;m<6;m++)
                                {
                                    if (Coul[(int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]]].cpt[m]>0)
                                    {
                                        cptadj++;
                                    }
                                }
                                //printf("%d",cptadj);
                                if (cptadj>4){
                                    Coul[(int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]]].cpt[col]--;
                                    Coul[col].cpt[(int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]]]--;
                                }

                                if (Coul[(int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]]].cpt[col]>3)
                                {
                                    ver3=-1;
                                    Coul[(int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]]].cpt[col]--;
                                    Coul[col].cpt[(int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]]]--;
                                }
                            }
                        }

                        if (Tab.ver2==1)
                        {
                            if ((int)rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]] == (int)color_select(col))
                            {
                                versame=1;
                            }

                            if ((int)rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]]<6 && (int)rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]]>=0)
                            {
                                Coul[(int)rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]]].cpt[col]++;
                                verjsp2=1;
                                //printf("rentre");
                                //printf("%d",Coul[col].cpt[col]);
                                for (m=0;m<6;m++)
                                {
                                    if (Coul[(int)rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]]].cpt[m]>0 )
                                    {
                                        cptadj2++;
                                        //printf("rentre2");
                                    }
                                }
                                //printf("%d",cptadj);
                                if (cptadj2>4)
                                {
                                    Coul[(int)rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]]].cpt[col]--;
                                    Coul[col].cpt[(int)rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]]]--;
                                }

                                if (Coul[(int)rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]]].cpt[col]>3)
                                {
                                    ver32=-1;
                                    Coul[(int)rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]]].cpt[col]--;
                                    Coul[col].cpt[(int)rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]]]--;
                                }

                            }
                        }

                        cptadj=0;
                        cptadj2=0;
                    }

                    /*printf("%d %d\n",select_color(rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]]),col);
                    printf("%d,%d\n",Tab.coor2[0],Tab.coor2[1]);
                    printf("%d",Tab.face2);*/

                    if (versame!=1 && ver32!=-1 && ver3!=-1 && verpos==0 && verla==0 && vercol==0)
                    {
                        rubiks[face].Tab2D[coorx][coory] = color_select(col);
                    }

                    else
                    {
                        Coul[col].nbocc--;
                        if ((coorx==0 && coory==1) || (coorx==1 && coory==0) || (coorx==1 && coory==2) || (coorx==2 && coory==1)) {
                            Coul[col].Arete--;
                        }
                        if ((coorx==0 && coory==0) || (coorx==0 && coory==2) || (coorx==2 && coory==0) || (coorx==2 && coory==2)) {
                            Coul[col].Sommet--;
                        }

                        if (coorx==1 && coory==1) {
                            Coul[col].Centre--;
                        }

                        if (verjsp==1 && ver3!=-1)
                        {
                            Coul[(int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]]].cpt[col]--;
                            Coul[col].cpt[(int)rubiks[Tab.face].Tab2D[Tab.coor[0]][Tab.coor[1]]]--;
                        }

                        if (verjsp2==1 && ver32!=-1)
                        {
                            Coul[(int)rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]]].cpt[col]--;
                            Coul[col].cpt[(int)rubiks[Tab.face2].Tab2D[Tab.coor2[0]][Tab.coor2[1]]]--;
                        }

                    }
                    verjsp=0;
                    verjsp2=0;



                }while(versame==1 || ver3==-1 || ver32==-1 || verpos!=0 || verla==-1 || vercol==-1);
            }
        }

        display_rubiks(rubiks);
        printf("\n\n");
    }

    return rubiks;
}



void BACK_clockwise(Face* rubiks,int type)
{
    int i, j, k, l, temp1,temp2,stk1=3,stk2=5;
    int stkf[3];
    for (i=0;i<type;i++) {
        stk1=3;
        stk2=5;
        for (k=0;k<3;k++)
        {
            stkf[k]=rubiks[stk1].Tab2D[k][2];
        }
        temp1 = rubiks[4].Tab2D[0][0];
        rubiks[4].Tab2D[0][0] = rubiks[4].Tab2D[2][0];
        rubiks[4].Tab2D[2][0] = rubiks[4].Tab2D[2][2];
        rubiks[4].Tab2D[2][2] = rubiks[4].Tab2D[0][2];
        rubiks[4].Tab2D[0][2] = temp1;
        temp2 = rubiks[4].Tab2D[1][0];
        rubiks[4].Tab2D[1][0] = rubiks[4].Tab2D[2][1];
        rubiks[4].Tab2D[2][1] = rubiks[4].Tab2D[1][2];
        rubiks[4].Tab2D[1][2] = rubiks[4].Tab2D[0][1];
        rubiks[4].Tab2D[0][1] = temp2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][2] = rubiks[stk2].Tab2D[2][2-k];
        }

        stk1 = 5;
        stk2=1;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2][k] = rubiks[stk2].Tab2D[k][0];
        }

        stk1=1;
        stk2=0;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][0] = rubiks[stk2].Tab2D[0][2-k];
        }

        stk1=0;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[0][k] = stkf[k];
        }

    }

}



void FRONT_clockwise(Face* rubiks,int type)
{
    int i, j, k, l,face, temp1,temp2,stk1=3,stk2=5;
    int stkf[3];
    for (i=0;i<type;i++) {
        stk1=3;
        stk2=0;
        for (k=0;k<3;k++)
        {
            stkf[k]=rubiks[stk1].Tab2D[k][0];
        }

        face = 2;
        temp1 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = temp1;
        temp2 = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = temp2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][0] = rubiks[stk2].Tab2D[2][k];
        }

        stk1 =0;
        stk2=1;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2][k] = rubiks[stk2].Tab2D[2-k][2];
        }

        stk1=1;
        stk2=5;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][2] = rubiks[stk2].Tab2D[0][k];
        }

        stk1=stk2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[0][k] = stkf[2-k];
        }

    }

}


void UP_clockwise(Face* rubiks,int type)
{
    int i, j, k, l,face, temp1,temp2,stk1=3,stk2=4;
    int stkf[3];
    for (i=0;i<type;i++) {
        stk1=3;
        stk2=4;
        for (k=0;k<3;k++)
        {
            stkf[k]=rubiks[stk1].Tab2D[0][k];
        }

        face = 0;
        temp1 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = temp1;
        temp2 = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = temp2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[0][k] = rubiks[stk2].Tab2D[0][k];
        }

        stk1 =stk2;
        stk2=1;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[0][k] = rubiks[stk2].Tab2D[0][k];
        }

        stk1=stk2;
        stk2=2;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[0][k] = rubiks[stk2].Tab2D[0][k];
        }

        stk1=stk2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[0][k] = stkf[k];
        }

    }

}



void DOWN_clockwise(Face* rubiks,int type)
{
    int i, j, k, l,face, temp1,temp2,stk1,stk2;
    int stkf[3];
    for (i=0;i<type;i++) {
        stk1=3;
        stk2=2;
        for (k=0;k<3;k++)
        {
            stkf[k]=rubiks[stk1].Tab2D[2][k];
        }

        face = 5;
        temp1 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = temp1;
        temp2 = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = temp2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2][k] = rubiks[stk2].Tab2D[2][k];
        }

        stk1 =stk2;
        stk2=1;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2][k] = rubiks[stk2].Tab2D[2][k];
        }

        stk1=stk2;
        stk2=4;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2][k] = rubiks[stk2].Tab2D[2][k];
        }

        stk1=stk2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2][k] = stkf[k];
        }

    }

}



void LEFT_clockwise(Face* rubiks,int type)
{
    int i, j, k, l,face, temp1,temp2,stk1,stk2;
    int stkf[3];
    for (i=0;i<type;i++) {
        stk1=5;
        stk2=2;
        for (k=0;k<3;k++)
        {
            stkf[k]=rubiks[stk1].Tab2D[k][0];
        }

        face = 1;
        temp1 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = temp1;
        temp2 = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = temp2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][0] = rubiks[stk2].Tab2D[k][0];
        }

        stk1 =stk2;
        stk2=0;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][0] = rubiks[stk2].Tab2D[k][0];
        }

        stk1=stk2;
        stk2=4;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2-k][0] = rubiks[stk2].Tab2D[k][2];
        }

        stk1=stk2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][2] = stkf[2-k];
        }

    }

}



void RIGHT_clockwise(Face* rubiks,int type)
{
    int i, j, k, l,face, temp1,temp2,stk1,stk2;
    int stkf[3];
    for (i=0;i<type;i++) {
        stk1=5;
        stk2=4;
        for (k=0;k<3;k++)
        {
            stkf[k]=rubiks[stk1].Tab2D[k][2];
        }

        face =3;
        temp1 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = temp1;
        temp2 = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = temp2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][2] = rubiks[stk2].Tab2D[2-k][0];
        }

        stk1 =stk2;
        stk2=0;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][0] = rubiks[stk2].Tab2D[2-k][2];
        }

        stk1=stk2;
        stk2=2;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][2] = rubiks[stk2].Tab2D[k][2];
        }

        stk1=stk2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][2] = stkf[k];
        }

    }

}

void BACK_anticlockwise(Face* rubiks,int type)
{
    int i, j, k, l,face, temp1,temp2,stk1,stk2;
    int stkf[3];
    for (i=0;i<type;i++) {
        stk1=3;
        stk2=0;
        for (k=0;k<3;k++)
        {
            stkf[k]=rubiks[stk1].Tab2D[2-k][2];
        }

        face =4;
        temp1 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = temp1;
        temp2 = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = temp2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][2] = rubiks[stk2].Tab2D[0][k];
        }

        stk1 =stk2;
        stk2=1;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[0][k] = rubiks[stk2].Tab2D[2-k][0];
        }

        stk1=stk2;
        stk2=5;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][0] = rubiks[stk2].Tab2D[2][k];
        }

        stk1=stk2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2][k] = stkf[k];
        }

    }

}



void FRONT_anticlockwise(Face* rubiks,int type)
{
    int i, j, k, l,face, temp1,temp2,stk1,stk2;
    int stkf[3];
    for (i=0;i<type;i++) {
        stk1=0;
        stk2=3;
        for (k=0;k<3;k++)
        {
            stkf[k]=rubiks[stk1].Tab2D[2][k];
        }

        face =2;
        temp1 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = temp1;
        temp2 = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = temp2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2][k] = rubiks[stk2].Tab2D[k][0];
        }

        stk1 =stk2;
        stk2=5;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][0] = rubiks[stk2].Tab2D[0][2-k];
        }

        stk1=stk2;
        stk2=1;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[0][k] = rubiks[stk2].Tab2D[k][2];
        }

        stk1=stk2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][2] = stkf[2-k];
        }

    }

}

void UP_anticlockwise(Face* rubiks,int type)
{
    int i, j, k, l,face, temp1,temp2,stk1,stk2;
    int stkf[3];
    for (i=0;i<type;i++) {
        stk1=2;
        stk2=1;
        for (k=0;k<3;k++)
        {
            stkf[k]=rubiks[stk1].Tab2D[0][k];
        }

        face =0;
        temp1 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = temp1;
        temp2 = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = temp2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[0][k] = rubiks[stk2].Tab2D[0][k];
        }

        stk1 =stk2;
        stk2=4;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[0][k] = rubiks[stk2].Tab2D[0][k];
        }

        stk1=stk2;
        stk2=3;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[0][k] = rubiks[stk2].Tab2D[0][k];
        }

        stk1=stk2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[0][k] = stkf[k];
        }

    }

}


void DOWN_anticlockwise(Face* rubiks,int type)
{
    int i, j, k, l,face, temp1,temp2,stk1,stk2;
    int stkf[3];
    for (i=0;i<type;i++) {
        stk1=2;
        stk2=3;
        for (k=0;k<3;k++)
        {
            stkf[k]=rubiks[stk1].Tab2D[2][k];
        }

        face =5;
        temp1 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = temp1;
        temp2 = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = temp2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2][k] = rubiks[stk2].Tab2D[2][k];
        }

        stk1 =stk2;
        stk2=4;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2][k] = rubiks[stk2].Tab2D[2][k];
        }

        stk1=stk2;
        stk2=1;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2][k] = rubiks[stk2].Tab2D[2][k];
        }

        stk1=stk2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[2][k] = stkf[k];
        }

    }

}



void RIGHT_anticlockwise(Face* rubiks,int type)
{
    int i, j, k, l,face, temp1,temp2,stk1,stk2;
    int stkf[3];
    for (i=0;i<type;i++) {
        stk1=2;
        stk2=0;
        for (k=0;k<3;k++)
        {
            stkf[k]=rubiks[stk1].Tab2D[k][2];
        }

        face =3;
        temp1 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = temp1;
        temp2 = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = temp2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][2] = rubiks[stk2].Tab2D[k][2];
        }

        stk1 =stk2;
        stk2=4;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][2] = rubiks[stk2].Tab2D[2-k][0];
        }

        stk1=stk2;
        stk2=5;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][0] = rubiks[stk2].Tab2D[2-k][2];
        }

        stk1=stk2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][2] = stkf[k];
        }

    }

}



void LEFT_anticlockwise(Face* rubiks,int type)
{
    int i, j, k, l,face, temp1,temp2,stk1,stk2;
    int stkf[3];
    for (i=0;i<type;i++) {
        stk1=2;
        stk2=5;
        for (k=0;k<3;k++)
        {
            stkf[k]=rubiks[stk1].Tab2D[k][0];
        }

        face =1;
        temp1 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = temp1;
        temp2 = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = temp2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][0] = rubiks[stk2].Tab2D[k][0];
        }

        stk1 =stk2;
        stk2=4;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][0] = rubiks[stk2].Tab2D[2-k][2];
        }

        stk1=stk2;
        stk2=0;
        for(k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][2] = rubiks[stk2].Tab2D[2-k][0];
        }

        stk1=stk2;
        for (k=0;k<3;k++)
        {
            rubiks[stk1].Tab2D[k][0] = stkf[k];
        }

    }

}



void horizontal_rotation(Face* rubiks) {
    int temp1[3][3],temp2[3][3],i,face=0,temp11,temp22;
    for (i=0;i<2;i++)
    {
        temp11 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = temp11;
        temp22 = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = temp22;
    }
    face=5;
    for (i=0;i<2;i++)
    {
        temp11 = rubiks[face].Tab2D[0][0];
        rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[2][0];
        rubiks[face].Tab2D[2][0] = rubiks[face].Tab2D[2][2];
        rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[0][2];
        rubiks[face].Tab2D[0][2] = temp11;
        temp22 = rubiks[face].Tab2D[1][0];
        rubiks[face].Tab2D[1][0] = rubiks[face].Tab2D[2][1];
        rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][2];
        rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[0][1];
        rubiks[face].Tab2D[0][1] = temp22;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp1[i][j] = rubiks[2].Tab2D[i][j];
            rubiks[2].Tab2D[i][j] = rubiks[4].Tab2D[i][j];
            rubiks[4].Tab2D[i][j] = temp1[i][j];
            temp2[i][j] = rubiks[3].Tab2D[i][j];
            rubiks[3].Tab2D[i][j] = rubiks[1].Tab2D[i][j];
            rubiks[1].Tab2D[i][j] = temp2[i][j];
        }
    }
}

void horizontal_rotation2(Face* rubiks) {
    int temp11[3][3],i,temp1,face=0,temp2;
    temp1 = rubiks[face].Tab2D[0][0];
    rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[2][0];
    rubiks[face].Tab2D[2][0] = rubiks[face].Tab2D[2][2];
    rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[0][2];
    rubiks[face].Tab2D[0][2] = temp1;
    temp2 = rubiks[face].Tab2D[1][0];
    rubiks[face].Tab2D[1][0] = rubiks[face].Tab2D[2][1];
    rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][2];
    rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[0][1];
    rubiks[face].Tab2D[0][1] = temp2;
    face=5;
    temp1 = rubiks[face].Tab2D[0][0];
    rubiks[face].Tab2D[0][0] = rubiks[face].Tab2D[0][2];
    rubiks[face].Tab2D[0][2] = rubiks[face].Tab2D[2][2];
    rubiks[face].Tab2D[2][2] = rubiks[face].Tab2D[2][0];
    rubiks[face].Tab2D[2][0] = temp1;
    temp2 = rubiks[face].Tab2D[0][1];
    rubiks[face].Tab2D[0][1] = rubiks[face].Tab2D[1][2];
    rubiks[face].Tab2D[1][2] = rubiks[face].Tab2D[2][1];
    rubiks[face].Tab2D[2][1] = rubiks[face].Tab2D[1][0];
    rubiks[face].Tab2D[1][0] = temp2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp11[i][j] = rubiks[1].Tab2D[i][j];
            rubiks[1].Tab2D[i][j] = rubiks[2].Tab2D[i][j];
            rubiks[2].Tab2D[i][j] = rubiks[3].Tab2D[i][j];
            rubiks[3].Tab2D[i][j] = rubiks[4].Tab2D[i][j];
            rubiks[4].Tab2D[i][j] = temp11[i][j];
        }
    }
}


void vertical_rotation(Face* rubiks){
    int temp1[3][3],temp2[3][3],i,j,k,to[3];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            temp1[i][j]= rubiks[0].Tab2D[i][j];
            rubiks[0].Tab2D[i][j] = rubiks[5].Tab2D[i][j];
            rubiks[5].Tab2D[i][j] = temp1[i][j];
            temp2[i][j] = rubiks[2].Tab2D[i][j];
            rubiks[2].Tab2D[i][j] = rubiks[4].Tab2D[i][j];
            rubiks[4].Tab2D[i][j] = temp2[i][j];
        }
    }

    for (i=1;i<5;i++)
    {
        for (j=0;j<3;j++)
        {
            to[j] = rubiks[i].Tab2D[0][j];
            rubiks[i].Tab2D[0][j] = rubiks[i].Tab2D[2][j];
            rubiks[i].Tab2D[2][j] = to[j];
        }
    }

    for (i=1;i<5;i++)
    {
        for(k=0;k<3;k++) {
            to[k] = rubiks[i].Tab2D[k][2];
            rubiks[i].Tab2D[k][2] = rubiks[i].Tab2D[k][0];
            rubiks[i].Tab2D[k][0]=to[k];
        }
    }
}

void move_rubiks(Face* rubiks){
    int face=-1,sens,x,rot=-1,mvt;
    while (rot!=3) {
        c_textcolor(BLUE);
        printf("\nChoisissez le type de la rotation :\n1 : ROTATION DE FACE   2 : ROTATION DU CUBE    3 : QUIT\n");
        scanf("%d",&rot);
        if (rot==1) {
            printf("\nChoisissez une face a tourner : \n0 : UP    1 : LEFT    2 : FRONT    3 : RIGHT    4 : BACK    5 : DOWN\n");
            scanf("%d", &face);
            printf("\nChoisissez un sens : \n1 : HORAIRE    2 : ANTI-HORAIRE\n");
            scanf("%d", &sens);
            printf("\nChoisissez la longueur de la rotation : \n1 : QUART-DE-TOUR    2 : DEMI-TOUR\n");
            scanf("%d", &x);
            if (sens == 1) {
                if (x == 1 || x == 2) {
                    if (face == 4)
                        BACK_clockwise(rubiks, x);
                    else if (face == 2)
                        FRONT_clockwise(rubiks, x);
                    else if (face == 0)
                        UP_clockwise(rubiks, x);
                    else if (face == 5)
                        DOWN_clockwise(rubiks, x);
                    else if (face == 1)
                        LEFT_clockwise(rubiks, x);
                    else if (face == 3)
                        RIGHT_clockwise(rubiks, x);
                }
            } else if (sens == 2) {
                if (x == 1 || x == 2) {
                    if (face == 4)
                        BACK_anticlockwise(rubiks, x);
                    else if (face == 2)
                        FRONT_anticlockwise(rubiks, x);
                    else if (face == 0)
                        UP_anticlockwise(rubiks, x);
                    else if (face == 5)
                        DOWN_anticlockwise(rubiks, x);
                    else if (face == 3)
                        RIGHT_anticlockwise(rubiks, x);
                    else if (face == 1)
                        LEFT_anticlockwise(rubiks, x);
                }
            }
            printf("\n");
            display_rubiks(rubiks);
        }
        else if (rot==2)
        {
            printf("\n1 : MOUVEMENT VERTICAL    2 : MOUVEMENT HORIZONTAL\n");
            scanf("%d",&mvt);
            if (mvt==1)
                vertical_rotation(rubiks);
            else if (mvt==2)
                horizontal_rotation(rubiks);
            display_rubiks(rubiks);
        }
    }
}

void scramble_rubiks(Face* rubiks)
{
    int i,j;

    for(j=0;j<10+rand()%10;j++){
        i=rand() % 14;
        if(i==0){
            FRONT_clockwise(rubiks,1+rand()%2);
        }
        if(i==1){
            BACK_clockwise(rubiks, 1+rand()%2);
        }
        if(i==2){
            UP_clockwise(rubiks, 1+rand()%2);
        }
        if(i==3){
            DOWN_clockwise(rubiks, 1+rand()%2);
        }
        if(i==4){
            RIGHT_clockwise(rubiks, 1+rand()%2);
        }
        if(i==5){
            LEFT_clockwise(rubiks, 1+rand()%2);
        }
        if(i==6){
            FRONT_anticlockwise(rubiks, 1+rand()%2);
        }
        if(i==7){
            BACK_anticlockwise(rubiks, 1+rand()%2);
        }
        if(i==8){
            UP_anticlockwise(rubiks, 1+rand()%2);
        }
        if(i==9){
            DOWN_anticlockwise(rubiks, 1+rand()%2);
        }
        if(i==10){
            RIGHT_anticlockwise(rubiks, 1+rand()%2);
        }
        if(i==11){
            LEFT_anticlockwise(rubiks, 1+rand()%2);
        }
        if(i==12){
            horizontal_rotation(rubiks);
        }
        if(i==13){
            vertical_rotation(rubiks);
        }
    }
}

void free_rubiks(Face* rubiks)
{
    int i,j,k;
    for (i=0;i<6;i++)
    {
        for (j=0;j<3;j++)
        {
            free((rubiks+i)->Tab2D[j]);
        }
    }

    for (i=0;i<6;i++)
    {
        free((rubiks+i)->Tab2D);
    }

    free(rubiks);

}



void croix_parfaite_UP(Face* rubiks)
{
    int col_case = (int)rubiks[0].Tab2D[1][1], ver,i;
    for (i=0;i<4;i++) {
        do {
            //1
            ver = 0;
            if (/*(int) rubiks[0].Tab2D[0][1] == col_case && (int) rubiks[0].Tab2D[1][0] == col_case &&
                (int) rubiks[0].Tab2D[1][2] == col_case && */(int) rubiks[2].Tab2D[0][1] == col_case &&
                                                             (int) rubiks[0].Tab2D[2][1] == (int) rubiks[2].Tab2D[1][1] &&
                                                             (int) rubiks[3].Tab2D[0][1] == (int) rubiks[3].Tab2D[1][1]) {
                FRONT_clockwise(rubiks, 1);
                UP_anticlockwise(rubiks, 1);
                RIGHT_clockwise(rubiks, 1);
                UP_clockwise(rubiks, 1);
                ver = 1;
            }
            //2
            if (/*(int) rubiks[0].Tab2D[0][1] == col_case && (int) rubiks[0].Tab2D[1][0] == col_case &&
                (int) rubiks[0].Tab2D[1][2] == col_case && */(int) rubiks[3].Tab2D[0][1] == (int) rubiks[3].Tab2D[1][1] &&
                                                             (int) rubiks[2].Tab2D[1][1] == (int) rubiks[5].Tab2D[0][1]) {
                FRONT_anticlockwise(rubiks, 1);
                RIGHT_anticlockwise(rubiks, 1);
                DOWN_anticlockwise(rubiks, 1);
                RIGHT_clockwise(rubiks, 1);
                FRONT_anticlockwise(rubiks, 2);
                ver = 1;
            }
            //3
            if (/*(int) rubiks[0].Tab2D[1][2] == col_case && (int) rubiks[0].Tab2D[1][0] == col_case &&
                (int) rubiks[0].Tab2D[1][2] == col_case && */(int) rubiks[2].Tab2D[1][2] == col_case &&
                                                             (int) rubiks[2].Tab2D[1][1] == (int) rubiks[3].Tab2D[1][0] &&
                                                             (int) rubiks[3].Tab2D[0][1] == (int) rubiks[3].Tab2D[1][1]) {
                RIGHT_anticlockwise(rubiks, 1);
                DOWN_anticlockwise(rubiks, 1);
                RIGHT_clockwise(rubiks, 1);
                FRONT_anticlockwise(rubiks, 2);
                ver = 1;
            }
            //4
            if ((int) rubiks[2].Tab2D[0][1] == col_case && (int) rubiks[0].Tab2D[2][1] == (int) rubiks[3].Tab2D[1][1]) {
                FRONT_clockwise(rubiks, 1);
                RIGHT_clockwise(rubiks, 1);
                ver = 1;
            }
            //5
            if ((int) rubiks[3].Tab2D[0][1] == col_case && (int) rubiks[0].Tab2D[1][2] == rubiks[1].Tab2D[1][1]) {
                RIGHT_anticlockwise(rubiks, 1);
                FRONT_anticlockwise(rubiks, 1);
                UP_clockwise(rubiks, 1);
                ver = 1;
            }
        } while ((col_case != rubiks[0].Tab2D[0][1] || col_case != rubiks[0].Tab2D[1][0] ||
                  col_case != rubiks[0].Tab2D[1][2] || col_case != rubiks[0].Tab2D[2][1]) && ver == 1);
        horizontal_rotation2(rubiks);
    }
}

void coincoin(Face* rubiks)
{
    Box Coin;
    int coorx=2,coory=2,face=2,col_case=rubiks[0].Tab2D[1][1],col_case2=rubiks[2].Tab2D[1][1],col_case3=rubiks[3].Tab2D[1][1],ver=0,cpt=0,i;
    //horizontal_rotation2(rubiks);
    Coin = adjacent(Coin,face,coorx,coory);
    //printf("ver : %d\nface : %d\ncoorx du 1 : %d\n coory du 1 :%d\nver2 : %d\nface2 : %d\n coorx du 2 : %d\n coory du 2 : %d\n",Coin.ver,Coin.face,Coin.coor[0],Coin.coor[1],Coin.ver2,Coin.face2,Coin.coor2[0],Coin.coor2[1]);
    if (Coin.ver2 == 1)
    {
        for (i=0;i<4;i++) {
            cpt=0;
            col_case=rubiks[0].Tab2D[1][1];
            col_case2=rubiks[2].Tab2D[1][1];
            col_case3=rubiks[3].Tab2D[1][1];
            do {
                if ((rubiks[face].Tab2D[coorx][coory] == col_case ||
                     rubiks[Coin.face].Tab2D[Coin.coor[0]][Coin.coor[1]] == col_case ||
                     rubiks[Coin.face2].Tab2D[Coin.coor2[0]][Coin.coor2[1]] == col_case)

                    && (rubiks[face].Tab2D[coorx][coory] == col_case2 ||
                        rubiks[Coin.face].Tab2D[Coin.coor[0]][Coin.coor[1]] == col_case2 ||
                        rubiks[Coin.face2].Tab2D[Coin.coor2[0]][Coin.coor2[1]] == col_case2)
                    && (rubiks[face].Tab2D[coorx][coory] == col_case3 ||
                        rubiks[Coin.face].Tab2D[Coin.coor[0]][Coin.coor[1]] == col_case3 ||
                        rubiks[Coin.face2].Tab2D[Coin.coor2[0]][Coin.coor2[1]] == col_case3)) {
                    //printf("rentre");
                    //printf("%d == %d == %d, %d == %d == %d\n",rubiks[2].Tab2D[0][0],rubiks[2].Tab2D[0][1],rubiks[2].Tab2D[1][1],rubiks[3].Tab2D[0][2],rubiks[3].Tab2D[0][1],rubiks[3].Tab2D[1][1]);
                    if (rubiks[2].Tab2D[0][0] == rubiks[2].Tab2D[0][1] &&
                        rubiks[2].Tab2D[0][0] == rubiks[2].Tab2D[1][1] &&
                        rubiks[3].Tab2D[0][2] == rubiks[3].Tab2D[0][1] &&
                        rubiks[3].Tab2D[0][2] == rubiks[3].Tab2D[1][1]) {
                        //printf("rentre");
                        do {
                            RIGHT_anticlockwise(rubiks, 1);
                            DOWN_anticlockwise(rubiks, 1);
                            RIGHT_clockwise(rubiks, 1);
                            DOWN_clockwise(rubiks, 1);
                            ver = 1;
                        } while (rubiks[0].Tab2D[2][2] != col_case);

                    }
                }
                //printf("%d",ver);
                if (ver==0)
                {
                    DOWN_clockwise(rubiks, 1);
                    cpt++;
                }
                //printf("\ncpt : %d\n",cpt);
                if (cpt == 4) {
                    ver = 1;
                    cpt=0;
                }
            } while (ver == 0);
            horizontal_rotation2(rubiks);
            ver=0;
        }
    }
}

void change1(Face* rubiks)
{
    blank_rubiks(rubiks);
    rubiks[0].Tab2D[0][1] = W;
    rubiks[0].Tab2D[1][0] =W;
    rubiks[0].Tab2D[1][1] = W;
    rubiks[0].Tab2D[1][2] = W;
    rubiks[0].Tab2D[2][1] = G;
    rubiks[2].Tab2D[0][1] = W;
    rubiks[2].Tab2D[1][1] = G;
    rubiks[3].Tab2D[0][1] = R;
    rubiks[3].Tab2D[1][1] = R;
}

void change2(Face* rubiks)
{
    blank_rubiks(rubiks);
    rubiks[0].Tab2D[0][1] = W;
    rubiks[0].Tab2D[1][0] =W;
    rubiks[0].Tab2D[1][1] = W;
    rubiks[0].Tab2D[1][2] = W;
    rubiks[2].Tab2D[1][1] = G;
    rubiks[5].Tab2D[0][1] = G;
    rubiks[2].Tab2D[2][1] = W;
    rubiks[3].Tab2D[0][1] = R;
    rubiks[3].Tab2D[1][1] = R;

}

void change3(Face* rubiks) {
    blank_rubiks(rubiks);
    rubiks[0].Tab2D[0][1] = W;
    rubiks[0].Tab2D[1][0] = W;
    rubiks[0].Tab2D[1][1] = W;
    rubiks[0].Tab2D[1][2] = W;
    rubiks[2].Tab2D[1][1] = G;
    rubiks[2].Tab2D[1][2] = W;
    rubiks[3].Tab2D[0][1] = R;
    rubiks[3].Tab2D[1][1] = R;
    rubiks[3].Tab2D[1][0] = G;

}

void change4(Face* rubiks) {
    blank_rubiks(rubiks);
    rubiks[0].Tab2D[1][1] = W;
    rubiks[0].Tab2D[2][1] = R;
    rubiks[2].Tab2D[0][1] = W;
    rubiks[2].Tab2D[1][1] = G;
    rubiks[3].Tab2D[1][1] = R;

}

void change5(Face* rubiks) {
    blank_rubiks(rubiks);
    rubiks[0].Tab2D[1][1] = W;
    rubiks[0].Tab2D[1][2] = O;
    rubiks[1].Tab2D[1][1] = O;
    rubiks[2].Tab2D[1][1] = G;
    rubiks[3].Tab2D[0][1] = W;
    rubiks[3].Tab2D[1][1] = R;


}




void change_coin1(Face* rubiks) {
    int i,j,k;
    blank_rubiks(rubiks);
    for (j=0;j<3;j++)
    {
        for (k=0;k<3;k++)
        {
            if (j!=2 || k!=2)
            {
                rubiks[0].Tab2D[j][k] = W;
            }
        }
    }

    rubiks[2].Tab2D[0][0] = O;
    rubiks[2].Tab2D[0][1] = O;
    rubiks[2].Tab2D[1][1] = O;

    rubiks[3].Tab2D[0][1] = G;
    rubiks[3].Tab2D[0][2] = G;
    rubiks[3].Tab2D[1][1] = G;

    rubiks[2].Tab2D[2][2] = G;
    rubiks[3].Tab2D[2][0] = W;
    rubiks[5].Tab2D[0][2] = O;

}


void change_coin2(Face* rubiks)
{
    int i,j,k;
    blank_rubiks(rubiks);
    for (j=0;j<3;j++)
    {
        for (k=0;k<3;k++)
        {
            if (j!=0 || k!=2)
            {
                rubiks[0].Tab2D[j][k] = W;
            }
        }
    }

    rubiks[3].Tab2D[0][0] = O;
    rubiks[3].Tab2D[0][1] = O;
    rubiks[3].Tab2D[1][1] = O;

    rubiks[4].Tab2D[0][1] = G;
    rubiks[4].Tab2D[0][2] = G;
    rubiks[4].Tab2D[1][1] = G;

    rubiks[3].Tab2D[2][2] = W;
    rubiks[4].Tab2D[2][0] = G;
    rubiks[5].Tab2D[2][2] = O;
}

void test(Face* rubiks)
{
    int i;
    blank_rubiks(rubiks);
    for (i=0;i<3;i++)
    {
        rubiks[2].Tab2D[2][i] = G;
        rubiks[3].Tab2D[2][i]=O;
    }
    rubiks[2].Tab2D[1][1]=G;
    rubiks[2].Tab2D[0][1]=G;
    rubiks[3].Tab2D[0][1]=O;
    rubiks[3].Tab2D[1][1] = O;
    rubiks[0].Tab2D[2][1]=O;
    rubiks[0].Tab2D[1][1] = Y;


}


void test2(Face* rubiks)
{
    int i;
    blank_rubiks(rubiks);
    for (i=0;i<3;i++)
    {
        rubiks[2].Tab2D[2][i] = G;
        rubiks[3].Tab2D[2][i]=O;
        rubiks[1].Tab2D[2][i]=R;
    }
    rubiks[2].Tab2D[1][1]=G;
    rubiks[2].Tab2D[0][1]=G;
    rubiks[3].Tab2D[0][1]=O;
    rubiks[3].Tab2D[1][1] = O;
    rubiks[0].Tab2D[2][1]=R;
    rubiks[0].Tab2D[1][1] = Y;
    rubiks[1].Tab2D[0][1]=R;
    rubiks[1].Tab2D[1][1]=R;
}


void testROT(Face* rubiks)
{
    int i;
    blank_rubiks(rubiks);
    for (i=0;i<3;i++)
    {
        rubiks[3].Tab2D[2][i] = G;
        rubiks[4].Tab2D[2][i]=O;
        rubiks[2].Tab2D[2][i]=R;
    }
    rubiks[3].Tab2D[1][1]=G;
    rubiks[3].Tab2D[0][1]=G;
    rubiks[4].Tab2D[0][1]=O;
    rubiks[4].Tab2D[1][1] = O;
    rubiks[0].Tab2D[0][1]=R;
    rubiks[0].Tab2D[1][1] = Y;
    rubiks[2].Tab2D[0][1]=R;
    rubiks[2].Tab2D[1][1]=R;
    rubiks[0].Tab2D[1][2]=G;
    rubiks[1].Tab2D[0][1]=R;
    rubiks[2].Tab2D[0][1]=R;
}


void couronne_2(Face* rubiks)
{
    int i,ver=0,cpt=0;
    //testROT(rubiks);
    //display_rubiks(rubiks);
    vertical_rotation(rubiks);
    for (i=0;i<4;i++)
    {
        do {
            if ((rubiks[0].Tab2D[2][1] == rubiks[2].Tab2D[1][1] && rubiks[2].Tab2D[0][1] == rubiks[3].Tab2D[1][1]) ||
                (rubiks[0].Tab2D[2][1] == rubiks[3].Tab2D[1][1] && rubiks[2].Tab2D[0][1] == rubiks[2].Tab2D[1][1])) {
                right_move(rubiks);
                ver=1;
            } else if ((rubiks[0].Tab2D[2][1] == rubiks[2].Tab2D[1][1] &&
                        rubiks[2].Tab2D[0][1] == rubiks[1].Tab2D[1][1]) ||
                       (rubiks[0].Tab2D[2][1] == rubiks[1].Tab2D[1][1] &&
                        rubiks[2].Tab2D[0][1] == rubiks[2].Tab2D[1][1])) {
                left_move(rubiks);
                ver=1;
            }
            else {
                UP_clockwise(rubiks, 1);
                cpt++;
            }
            //Mauvaise orientation
            if ((rubiks[2].Tab2D[1][2] == rubiks[3].Tab2D[1][1] && rubiks[3].Tab2D[1][0] == rubiks[2].Tab2D[1][1]) ||
                (rubiks[2].Tab2D[2][2] == rubiks[3].Tab2D[1][1] && rubiks[3].Tab2D[2][0] == rubiks[2].Tab2D[1][1])) {
                mauv(rubiks);
            }
            if (cpt>=4)
            {
                ver=1;
                cpt=0;
            }
        }while (ver==0);

        horizontal_rotation2(rubiks);
        //if (i==0)
        //    rubiks[2].Tab2D[0][1]=G;
        //else if (i==1)
        //    rubiks[2].Tab2D[0][1]=O;
        //printf("\n\n");
        //display_rubiks(rubiks);
    }



}

void right_move(Face* rubiks)
{
    UP_clockwise(rubiks,1);
    RIGHT_clockwise(rubiks,1);
    UP_anticlockwise(rubiks,1);
    RIGHT_anticlockwise(rubiks,1);
    UP_anticlockwise(rubiks,1);
    FRONT_anticlockwise(rubiks,1);
    UP_clockwise(rubiks,1);
    FRONT_clockwise(rubiks,1);
}

void left_move(Face* rubiks)
{
    UP_anticlockwise(rubiks,1);
    LEFT_anticlockwise(rubiks,1);
    UP_clockwise(rubiks,1);
    LEFT_clockwise(rubiks,1);
    UP_clockwise(rubiks,1);
    FRONT_clockwise(rubiks,1);
    UP_anticlockwise(rubiks,1);
    FRONT_anticlockwise(rubiks,1);
}


void mauv(Face* rubiks)
{
    UP_clockwise(rubiks,1);
    RIGHT_clockwise(rubiks,1);
    UP_anticlockwise(rubiks,1);
    RIGHT_anticlockwise(rubiks,1);
    UP_anticlockwise(rubiks,1);
    FRONT_anticlockwise(rubiks,1);
    UP_clockwise(rubiks,1);
    FRONT_clockwise(rubiks,1);
    UP_clockwise(rubiks,2);
    UP_clockwise(rubiks,1);
    RIGHT_clockwise(rubiks,1);
    UP_anticlockwise(rubiks,1);
    RIGHT_anticlockwise(rubiks,1);
    UP_anticlockwise(rubiks,1);
    FRONT_anticlockwise(rubiks,1);
    UP_clockwise(rubiks,1);
    FRONT_clockwise(rubiks,1);
}

void test_croix_jaune(Face* rubiks)
{
    int i,j,k;
    for (j=1;j<3;j++)
    {
        for (k=0;k<3;k++)
        {
            rubiks[1].Tab2D[j][k] = O;
            rubiks[2].Tab2D[j][k]=B;
            rubiks[3].Tab2D[j][k]=R;
            rubiks[4].Tab2D[j][k]=G;
        }
    }
    rubiks[2].Tab2D[0][0]=G;
    rubiks[2].Tab2D[0][2]=B;
    rubiks[4].Tab2D[0][0]=R;
    rubiks[4].Tab2D[0][2]=O;

    rubiks[0].Tab2D[0][0]=B;
    rubiks[1].Tab2D[1][2]=O;
    rubiks[1].Tab2D[1][0]=O;
    rubiks[0].Tab2D[2][0]=O;
    rubiks[0].Tab2D[1][0]=O;
    rubiks[0].Tab2D[0][1]=G;
    rubiks[0].Tab2D[2][1]=B;
    rubiks[0].Tab2D[2][2]=R;
    rubiks[0].Tab2D[0][2]=G;
    rubiks[0].Tab2D[1][2]=R;


    rubiks[1].Tab2D[0][0]=Y;
    rubiks[1].Tab2D[0][1]=Y;
    rubiks[1].Tab2D[0][2]=Y;
    rubiks[0].Tab2D[1][1]=Y;
    rubiks[3].Tab2D[0][0]=Y;
    rubiks[3].Tab2D[0][1]=Y;
    rubiks[3].Tab2D[0][2]=Y;
    rubiks[2].Tab2D[0][1]=Y;
    rubiks[4].Tab2D[0][1]=Y;

}


void test_L(Face* rubiks)
{
    int i,j,k;
    for (j=1;j<3;j++)
    {
        for (k=0;k<3;k++)
        {
            rubiks[1].Tab2D[j][k] = O;
            rubiks[2].Tab2D[j][k]=B;
            rubiks[3].Tab2D[j][k]=R;
            rubiks[4].Tab2D[j][k]=G;
        }
    }
    rubiks[2].Tab2D[0][0]=G;
    rubiks[2].Tab2D[0][2]=B;
    rubiks[4].Tab2D[0][0]=R;
    rubiks[4].Tab2D[0][2]=O;

    rubiks[0].Tab2D[0][0]=B;
    rubiks[1].Tab2D[1][2]=O;
    rubiks[1].Tab2D[1][0]=O;
    rubiks[0].Tab2D[2][0]=O;
    rubiks[0].Tab2D[1][0]=O;
    rubiks[0].Tab2D[0][1]=Y;
    rubiks[0].Tab2D[2][1]=B;
    rubiks[0].Tab2D[2][2]=R;
    rubiks[0].Tab2D[0][2]=G;
    rubiks[0].Tab2D[1][2]=Y;


    rubiks[1].Tab2D[0][0]=Y;
    rubiks[1].Tab2D[0][1]=Y;
    rubiks[1].Tab2D[0][2]=Y;
    rubiks[0].Tab2D[1][1]=Y;
    rubiks[3].Tab2D[0][0]=Y;
    rubiks[3].Tab2D[0][1]=R;
    rubiks[3].Tab2D[0][2]=Y;
    rubiks[2].Tab2D[0][1]=Y;
    rubiks[4].Tab2D[0][1]=G;

}


void test_barre(Face* rubiks)
{
    int i,j,k;
    for (j=1;j<3;j++)
    {
        for (k=0;k<3;k++)
        {
            rubiks[1].Tab2D[j][k] = O;
            rubiks[2].Tab2D[j][k]=B;
            rubiks[3].Tab2D[j][k]=R;
            rubiks[4].Tab2D[j][k]=G;
        }
    }
    rubiks[2].Tab2D[0][0]=G;
    rubiks[2].Tab2D[0][2]=B;
    rubiks[4].Tab2D[0][0]=R;
    rubiks[4].Tab2D[0][2]=O;

    rubiks[0].Tab2D[0][0]=B;
    rubiks[1].Tab2D[1][2]=O;
    rubiks[1].Tab2D[1][0]=O;
    rubiks[0].Tab2D[2][0]=O;
    rubiks[0].Tab2D[1][0]=Y;
    rubiks[0].Tab2D[0][1]=G;
    rubiks[0].Tab2D[2][1]=B;
    rubiks[0].Tab2D[2][2]=R;
    rubiks[0].Tab2D[0][2]=G;
    rubiks[0].Tab2D[1][2]=Y;


    rubiks[1].Tab2D[0][0]=Y;
    rubiks[1].Tab2D[0][1]=O;
    rubiks[1].Tab2D[0][2]=Y;
    rubiks[0].Tab2D[1][1]=Y;
    rubiks[3].Tab2D[0][0]=Y;
    rubiks[3].Tab2D[0][1]=R;
    rubiks[3].Tab2D[0][2]=Y;
    rubiks[2].Tab2D[0][1]=Y;
    rubiks[4].Tab2D[0][1]=Y;

}


void croix_jaune(Face* rubiks)
{
    int ver=0,cpt=0,cpt2=0,i,j,k,cpt3=0,cpt3_2=0;
    //CAS D UN SEUL POINT JAUNE
    //printf("%d != %")
    if ((rubiks[0].Tab2D[0][1]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[1][0]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[1][2]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[2][1]!=rubiks[0].Tab2D[1][1])
        && rubiks[0].Tab2D[0][0]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[2][0]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[0][2]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[2][2]!=rubiks[0].Tab2D[1][1])
    {
        //printf("rentre");
        RIGHT_anticlockwise(rubiks,1);
        UP_anticlockwise(rubiks,1);
        FRONT_anticlockwise(rubiks,1);
        UP_clockwise(rubiks,1);
        FRONT_clockwise(rubiks,1);
        RIGHT_clockwise(rubiks,1);
        FRONT_clockwise(rubiks,1);
        RIGHT_clockwise(rubiks,1);
        UP_clockwise(rubiks,1);
        RIGHT_anticlockwise(rubiks,1);
        UP_anticlockwise(rubiks,1);
        FRONT_anticlockwise(rubiks,1);
        do {
            UP_clockwise(rubiks,1);
        }while(rubiks[1].Tab2D[0][1]!=rubiks[1].Tab2D[1][1] && rubiks[2].Tab2D[0][1]!=rubiks[2].Tab2D[1][1] && rubiks[3].Tab2D[0][1]!=rubiks[3].Tab2D[1][1] && rubiks[4].Tab2D[0][1]!=rubiks[4].Tab2D[1][1]);
    }

    //CAS L
    do {
        horizontal_rotation2(rubiks);
        cpt++;
    }while(cpt<4 && (rubiks[0].Tab2D[1][0] != rubiks[0].Tab2D[1][1] || rubiks[0].Tab2D[0][1] != rubiks[0].Tab2D[1][1] || rubiks[0].Tab2D[0][0]==rubiks[0].Tab2D[1][1] ||
                     rubiks[0].Tab2D[0][2] == rubiks[0].Tab2D[1][1] || rubiks[0].Tab2D[1][2] == rubiks[0].Tab2D[1][1] || rubiks[0].Tab2D[2][0]
                                                                                                                         == rubiks[0].Tab2D[1][1]  || rubiks[0].Tab2D[2][1] == rubiks[0].Tab2D[1][1] || rubiks[0].Tab2D[2][2] == rubiks[0].Tab2D[1][1]));

    if (rubiks[0].Tab2D[1][0] == rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[0][1] == rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[0][0]!=rubiks[0].Tab2D[1][1] &&
        rubiks[0].Tab2D[0][2] != rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[1][2] != rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[2][0]
                                                                                                            != rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[2][1] != rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[2][2] != rubiks[0].Tab2D[1][1])
    {
        RIGHT_anticlockwise(rubiks,1);
        UP_anticlockwise(rubiks,1);
        FRONT_anticlockwise(rubiks,1);
        UP_clockwise(rubiks,1);
        FRONT_clockwise(rubiks,1);
        RIGHT_clockwise(rubiks,1);
    }

    //Cas barre jaune
    do {
        horizontal_rotation2(rubiks);
        cpt2++;
    }while(cpt2<4 && (rubiks[0].Tab2D[1][0]!=rubiks[0].Tab2D[1][1] || rubiks[0].Tab2D[1][2]!=rubiks[0].Tab2D[1][1]
                      || rubiks[0].Tab2D[0][0]==rubiks[0].Tab2D[1][1] || rubiks[0].Tab2D[0][1]==rubiks[0].Tab2D[1][1]
                      || rubiks[0].Tab2D[0][2]==rubiks[0].Tab2D[1][1] || rubiks[0].Tab2D[2][0]==rubiks[0].Tab2D[1][1]
                      || rubiks[0].Tab2D[2][1]==rubiks[0].Tab2D[1][1] || rubiks[0].Tab2D[2][2]==rubiks[0].Tab2D[1][1]));

    if (rubiks[0].Tab2D[1][0]==rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[1][2]==rubiks[0].Tab2D[1][1]
        && rubiks[0].Tab2D[0][0]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[0][1]!=rubiks[0].Tab2D[1][1] &&
        rubiks[0].Tab2D[0][2]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[2][0]!=rubiks[0].Tab2D[1][1] &&
        rubiks[0].Tab2D[2][1]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[2][2]!=rubiks[0].Tab2D[1][1])
    {
        FRONT_clockwise(rubiks,1);
        RIGHT_clockwise(rubiks,1);
        UP_clockwise(rubiks,1);
        RIGHT_anticlockwise(rubiks,1);
        UP_anticlockwise(rubiks,1);
        FRONT_anticlockwise(rubiks,1);
    }

    do {
        cpt3=0;
        UP_anticlockwise(rubiks,1);
        for (i=1;i<5;i++)
        {
            if (rubiks[i].Tab2D[0][1] == rubiks[i].Tab2D[1][1])
                cpt3++;
        }
        cpt3_2++;
    }while(cpt3_2<4 && cpt3<2);

    if (cpt3_2>=4 && cpt3<2) {
        cpt3_2 = 0;
        do {
            cpt3 = 0;
            UP_anticlockwise(rubiks, 1);
            for (i = 1; i < 5; i++) {
                if (rubiks[i].Tab2D[0][1] == rubiks[i].Tab2D[1][1])
                    cpt3++;
            }
            cpt3_2++;
        } while (cpt3_2 < 4 && cpt3 < 1);
    }



    //display_rubiks(rubiks);

    //TEST SI C UNE CROIX (PAS FORCEMENT PARFAITE)
    if (rubiks[0].Tab2D[1][1]==rubiks[0].Tab2D[0][1] && rubiks[0].Tab2D[1][1]==rubiks[0].Tab2D[1][0] && rubiks[0].Tab2D[1][1]==rubiks[0].Tab2D[1][2] && rubiks[0].Tab2D[1][1]==rubiks[0].Tab2D[2][1])
    {
        //TEST SI c’est une croix jaune avec deux arêtes face à face bien placées et deux arêtes mal placées
        if ((rubiks[1].Tab2D[0][1]==rubiks[1].Tab2D[1][1] && rubiks[3].Tab2D[0][1]==rubiks[3].Tab2D[1][1] && rubiks[2].Tab2D[0][1]!=rubiks[2].Tab2D[1][1] && rubiks[4].Tab2D[0][1]!=rubiks[4].Tab2D[1][1])
            || (rubiks[1].Tab2D[0][1]!=rubiks[1].Tab2D[1][1] && rubiks[3].Tab2D[0][1]!=rubiks[3].Tab2D[1][1] && rubiks[2].Tab2D[0][1]==rubiks[2].Tab2D[1][1] && rubiks[4].Tab2D[0][1]==rubiks[4].Tab2D[1][1]))
        {
            if (rubiks[2].Tab2D[0][1]!=rubiks[2].Tab2D[1][1])
            {
                horizontal_rotation2(rubiks);
            }
            RIGHT_clockwise(rubiks,1);
            UP_clockwise(rubiks,2);
            RIGHT_anticlockwise(rubiks,1);
            UP_anticlockwise(rubiks,1);
            RIGHT_clockwise(rubiks,1);
            UP_anticlockwise(rubiks,1);
            RIGHT_anticlockwise(rubiks,1);
        }

        //Si c’est une croix jaune avec deux arêtes côte à côte bien placées et deux arêtes mal placées
        if ((rubiks[1].Tab2D[0][1]==rubiks[1].Tab2D[1][1] && rubiks[2].Tab2D[0][1]==rubiks[2].Tab2D[1][1] && rubiks[3].Tab2D[0][1]!=rubiks[3].Tab2D[1][1] && rubiks[4].Tab2D[0][1]!=rubiks[4].Tab2D[1][1])
            || (rubiks[1].Tab2D[0][1]!=rubiks[1].Tab2D[1][1] && rubiks[2].Tab2D[0][1]==rubiks[2].Tab2D[1][1] && rubiks[3].Tab2D[0][1]==rubiks[3].Tab2D[1][1] && rubiks[4].Tab2D[0][1]!=rubiks[4].Tab2D[1][1])
            || (rubiks[1].Tab2D[0][1]!=rubiks[1].Tab2D[1][1] && rubiks[2].Tab2D[0][1]!=rubiks[2].Tab2D[1][1] && rubiks[3].Tab2D[0][1]==rubiks[3].Tab2D[1][1] && rubiks[4].Tab2D[0][1]==rubiks[4].Tab2D[1][1])
            || (rubiks[1].Tab2D[0][1]==rubiks[1].Tab2D[1][1] && rubiks[2].Tab2D[0][1]!=rubiks[2].Tab2D[1][1] && rubiks[3].Tab2D[0][1]!=rubiks[3].Tab2D[1][1] && rubiks[4].Tab2D[0][1]==rubiks[4].Tab2D[1][1]))
        {
            do {
                horizontal_rotation2(rubiks);
            }while(rubiks[2].Tab2D[0][1]==rubiks[2].Tab2D[1][1] || rubiks[3].Tab2D[0][1]==rubiks[3].Tab2D[1][1]);
            RIGHT_clockwise(rubiks,1);
            UP_clockwise(rubiks,2);
            RIGHT_anticlockwise(rubiks,1);
            UP_anticlockwise(rubiks,1);
            RIGHT_clockwise(rubiks,1);
            UP_anticlockwise(rubiks,1);
            RIGHT_anticlockwise(rubiks,1);
            UP_anticlockwise(rubiks,1);
        }


        if ((rubiks[1].Tab2D[0][1]==rubiks[1].Tab2D[1][1] && rubiks[3].Tab2D[0][1]==rubiks[3].Tab2D[1][1] && rubiks[2].Tab2D[0][1]==rubiks[2].Tab2D[1][1] && rubiks[4].Tab2D[0][1]==rubiks[4].Tab2D[1][1]))
        {
            ver=1;
        }
    }

}

void test_coin(Face* rubiks)
{
    int i,j,k;
    blank_rubiks(rubiks);
    for (j=1;j<3;j++)
    {
        for (k=0;k<3;k++)
        {
            rubiks[1].Tab2D[j][k]=O;
            rubiks[2].Tab2D[j][k]=B;
            rubiks[3].Tab2D[j][k]=R;
            rubiks[4].Tab2D[j][k]=G;
        }
    }
    for (i=1;i<5;i++)
    {
        rubiks[i].Tab2D[0][1] = rubiks[i].Tab2D[1][1];
    }
    rubiks[0].Tab2D[1][1] = Y;
    rubiks[0].Tab2D[0][1] = rubiks[0].Tab2D[1][1];
    rubiks[0].Tab2D[1][0] = rubiks[0].Tab2D[1][1];
    rubiks[0].Tab2D[1][2] = rubiks[0].Tab2D[1][1];
    rubiks[0].Tab2D[2][1] = rubiks[0].Tab2D[1][1];

    rubiks[0].Tab2D[0][0] = O;
    rubiks[4].Tab2D[0][2] = G;
    rubiks[1].Tab2D[0][0] = Y;

    rubiks[0].Tab2D[2][0] = R;
    rubiks[1].Tab2D[0][2] = O;
    rubiks[2].Tab2D[0][0] = Y;

    rubiks[0].Tab2D[2][2] = B;
    rubiks[2].Tab2D[0][2] = Y;
    rubiks[3].Tab2D[0][0] = G;

    rubiks[3].Tab2D[0][2] = O;
    rubiks[4].Tab2D[0][0] = Y;
    rubiks[0].Tab2D[0][2] = B;

}

void bienplacerlescoins(Face* rubiks)
{
    Box Coin;
    int i,j,k,cpt=0, stk;
    //CROIX PARFAITE?
    if (rubiks[0].Tab2D[1][1]==rubiks[0].Tab2D[0][1] && rubiks[0].Tab2D[1][1]==rubiks[0].Tab2D[1][0] && rubiks[0].Tab2D[1][1]==rubiks[0].Tab2D[1][2] && rubiks[0].Tab2D[1][1]==rubiks[0].Tab2D[2][1]
        && rubiks[1].Tab2D[0][1]==rubiks[1].Tab2D[1][1] && rubiks[3].Tab2D[0][1]==rubiks[3].Tab2D[1][1] && rubiks[2].Tab2D[0][1]==rubiks[2].Tab2D[1][1] && rubiks[4].Tab2D[0][1]==rubiks[4].Tab2D[1][1])
    {
        //4 COINS MAL PLACES???
        for (i=0;i<4;i++)
        {
            if ((rubiks[0].Tab2D[2][2]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[2][2]!=rubiks[2].Tab2D[1][1] && rubiks[0].Tab2D[2][2]!=rubiks[3].Tab2D[1][1])
                || (rubiks[2].Tab2D[0][2]!=rubiks[0].Tab2D[1][1] && rubiks[2].Tab2D[0][2]!=rubiks[2].Tab2D[1][1] && rubiks[2].Tab2D[0][2]!=rubiks[3].Tab2D[1][1])
                || (rubiks[3].Tab2D[0][0]!=rubiks[0].Tab2D[1][1] && rubiks[3].Tab2D[0][0]!=rubiks[2].Tab2D[1][1] && rubiks[3].Tab2D[0][0]!=rubiks[3].Tab2D[1][1]))
            {
                cpt++;
            }

            horizontal_rotation2(rubiks);
        }
        if (cpt==4)
        {
            LEFT_anticlockwise(rubiks,1);
            UP_clockwise(rubiks,1);
            RIGHT_clockwise(rubiks,1);
            UP_anticlockwise(rubiks,1);
            LEFT_clockwise(rubiks,1);
            UP_clockwise(rubiks,1);
            RIGHT_anticlockwise(rubiks,1);
            UP_anticlockwise(rubiks,1);
        }
        cpt=0;
        for (i=0;i<4;i++)
        {
            if ((rubiks[0].Tab2D[2][2]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[2][2]!=rubiks[2].Tab2D[1][1] && rubiks[0].Tab2D[2][2]!=rubiks[3].Tab2D[1][1])
                || (rubiks[2].Tab2D[0][2]!=rubiks[0].Tab2D[1][1] && rubiks[2].Tab2D[0][2]!=rubiks[2].Tab2D[1][1] && rubiks[2].Tab2D[0][2]!=rubiks[3].Tab2D[1][1])
                || (rubiks[3].Tab2D[0][0]!=rubiks[0].Tab2D[1][1] && rubiks[3].Tab2D[0][0]!=rubiks[2].Tab2D[1][1] && rubiks[3].Tab2D[0][0]!=rubiks[3].Tab2D[1][1]))
            {
                cpt++;
            }

            horizontal_rotation2(rubiks);
        }

        //horizontal_rotation2(rubiks);
        //horizontal_rotation2(rubiks);
        //horizontal_rotation2(rubiks);
        // (rubiks[0].Tab2D[2][2] == rubiks[0].Tab2D[1][1] || rubiks[0].Tab2D[2][2] == rubiks
        //display_rubiks(rubiks);

        if (cpt==3)
        {
            do {
                horizontal_rotation2(rubiks);
            }while(((rubiks[0].Tab2D[2][2]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[2][2]!=rubiks[2].Tab2D[1][1] && rubiks[0].Tab2D[2][2]!=rubiks[3].Tab2D[1][1])
                    || (rubiks[2].Tab2D[0][2]!=rubiks[0].Tab2D[1][1] && rubiks[2].Tab2D[0][2]!=rubiks[2].Tab2D[1][1] && rubiks[2].Tab2D[0][2]!=rubiks[3].Tab2D[1][1])
                    || (rubiks[3].Tab2D[0][0]!=rubiks[0].Tab2D[1][1] && rubiks[3].Tab2D[0][0]!=rubiks[2].Tab2D[1][1] && rubiks[3].Tab2D[0][0]!=rubiks[3].Tab2D[1][1])) &&

                   ((rubiks[0].Tab2D[2][0]!=rubiks[0].Tab2D[1][1] && rubiks[0].Tab2D[2][0]!=rubiks[2].Tab2D[1][1] && rubiks[0].Tab2D[2][0]!=rubiks[1].Tab2D[1][1])
                    || (rubiks[2].Tab2D[0][0]!=rubiks[0].Tab2D[1][1] && rubiks[2].Tab2D[0][0]!=rubiks[2].Tab2D[1][1] && rubiks[2].Tab2D[0][0]!=rubiks[1].Tab2D[1][1])
                    || (rubiks[1].Tab2D[0][2]!=rubiks[0].Tab2D[1][1] && rubiks[1].Tab2D[0][2]!=rubiks[2].Tab2D[1][1] && rubiks[1].Tab2D[0][2]!=rubiks[1].Tab2D[1][1])));

            if ((rubiks[0].Tab2D[2][2]==rubiks[0].Tab2D[1][1] || rubiks[0].Tab2D[2][2]==rubiks[2].Tab2D[1][1] || rubiks[0].Tab2D[2][2]==rubiks[3].Tab2D[1][1])
                && (rubiks[2].Tab2D[0][2]==rubiks[0].Tab2D[1][1] || rubiks[2].Tab2D[0][2]==rubiks[2].Tab2D[1][1] || rubiks[2].Tab2D[0][2]==rubiks[3].Tab2D[1][1])
                && (rubiks[3].Tab2D[0][0]==rubiks[0].Tab2D[1][1] || rubiks[3].Tab2D[0][0]==rubiks[2].Tab2D[1][1] || rubiks[3].Tab2D[0][0]==rubiks[3].Tab2D[1][1]))
            {
                //stk=rubiks[0].Tab2D
            }

        }
    }
}





void interface()
{
    int i,cpt=0,w=0,ver=0,w2=2,et=0;
    Face* rubiks = create_rubiks();

    while (w!=7)
    {
        c_textcolor(WHITE);
        for(i=0;i<91;i++)
        {
            printf("-");
        }
        printf("\n\n");
        if (ver==0)
        {
            printf("1: Scramble     2: Initialize     3: Blank     4: Play     5: Fill      6:Solve     7: Quit\n\n");
        }
        else
        {
            printf("1: Scramble     2: Reset     3: Blank     4: Play     5: Fill      6:Solve     7: Quit\n\n");
        }
        for(i=0;i<91;i++)
        {
            printf("-");
        }
        printf("\n");
        printf("Action : ");
        scanf("%d",&w);
        if (w==1)
        {
            if (ver==0)
            {
                printf("You should first initialize the rubiks.\n");
            }
            else
            {
                scramble_rubiks(rubiks);
            }
        }

        if (w==2)
        {
            init_rubiks(rubiks);
            ver=1;
        }

        if (w==3)
        {
            blank_rubiks(rubiks);
            ver=1;
        }

        if (w==4)
        {
            if (ver==0)
            {
                printf("You should first initialize the rubiks.\n");
            }
            else
            {
                move_rubiks(rubiks);
            }
        }

        if (w==5)
        {
            fill_rubiks(rubiks);
            ver=1;
        }

        if (w==6)
        {
            if (ver==0)
            {
                printf("You should first initialize the rubiks.\n");
            }
            else
            {
                if (et==0)
                {
                    croix_parfaite_UP(rubiks);
                    display_rubiks(rubiks);
                    printf("\n\n");
                    c_textcolor(WHITE);
                    printf("Do you want to get to the next step?\n1: Yes     2: No\nChoice : ");
                    scanf("%d",&w2);
                    if(w2==1)
                    {
                        et=1;
                    }
                }

                if (et==1)
                {
                    coincoin(rubiks);
                    display_rubiks(rubiks);
                    printf("\n\n");
                    c_textcolor(WHITE);
                    printf("Do you want to get to the next step?\n1: Yes     2: No\nChoice : ");
                    scanf("%d",&w2);
                    if(w2==1)
                    {
                        et=2;
                    }
                }

                if (et==2)
                {
                    couronne_2(rubiks);
                    display_rubiks(rubiks);
                    printf("\n\n");
                    c_textcolor(WHITE);
                    printf("Do you want to get to the next step?\n1: Yes     2: No\nChoice : ");
                    scanf("%d",&w2);
                    if(w2==1)
                    {
                        et=3;
                    }
                }

                if (et==3)
                {
                    croix_jaune(rubiks);
                    display_rubiks(rubiks);
                    printf("\n\n");
                    c_textcolor(WHITE);
                    printf("Do you want to get to the next step?\n1: Yes     2: No\nChoice : ");
                    scanf("%d",&w2);
                    if(w2==1)
                    {
                        et=4;
                    }
                }

                if (et==4)
                {
                    bienplacerlescoins(rubiks);
                    display_rubiks(rubiks);
                    printf("\n\n");
                    c_textcolor(WHITE);
                    printf("Do you want to get to the next step?\n1: Yes     2: No\nChoice : ");
                    scanf("%d",&w2);
                    if(w2==1)
                    {
                        et=5;
                    }
                }

                if (w2!=1)
                {
                    et++;
                    w2=2;
                }
            }
        }
        if (ver==1 && w2==2)
        {
            printf("\n");
            display_rubiks(rubiks);
            printf("\n\n");
        }

    }
}


