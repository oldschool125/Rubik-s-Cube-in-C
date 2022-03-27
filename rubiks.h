//
// Created by windows on 4/20/2021.
//

#ifndef PROJET_C_RUBIKS_H
#define PROJET_C_RUBIKS_H


#include <stdio.h>
#include <stdlib.h>

typedef enum { R, B, G, W, Y, O, LG } T_COLOR ;
typedef enum { FRONT, BACK, UP, DOWN, RIGHT, LEFT } T_SIDE ;

typedef struct
{
    T_COLOR** Tab2D;
    T_SIDE Nom_Face;
}Face;

typedef struct
{
    int ver;
    int coor[2];
    int face;
    int ver2;
    int coor2[2];
    int face2;
    int val;
}Box;

typedef struct
{
    int nbocc;
    int Sommet;
    int Arete;
    int Centre;
    int cpt[6];
}Col;

int select_color(T_COLOR color);
int side_to_index(T_SIDE side);
T_SIDE index_to_side(int side);
T_COLOR color_select(int color);
Face* init_rubiks(Face* rubiks);
void display_rubiks(Face* rubiks);
Face* blank_rubiks(Face* rubiks);
Face * fill_rubiks(Face* rubiks);
Face* create_rubiks();
void FRONT_clockwise(Face* rubiks,int type);
void BACK_clockwise(Face* rubiks,int type);
void UP_clockwise(Face* rubiks,int type);
void DOWN_clockwise(Face* rubiks,int type);
void RIGHT_clockwise(Face* rubiks,int type);
void LEFT_clockwise(Face* rubiks,int type);
void FRONT_anticlockwise(Face* rubiks, int type);
void BACK_anticlockwise(Face* rubiks, int type);
void UP_anticlockwise(Face* rubiks, int type);
void DOWN_anticlockwise(Face* rubiks, int type);
void RIGHT_anticlockwise(Face* rubiks, int type);
void LEFT_anticlockwise(Face* rubiks, int type);
void horizontal_rotation(Face* rubiks);
void vertical_rotation(Face* rubiks);
void move_rubiks(Face* rubiks);
void scramble_rubiks(Face* rubiks);
void free_rubiks(Face* rubiks);
void croix_parfaite_UP(Face* rubiks);
void change1(Face* rubiks);
void change2(Face* rubiks);
void change3(Face* rubiks);
void change4(Face* rubiks);
void change5(Face* rubiks);
void horizontal_rotation2(Face* rubiks);
void change_coin1(Face* rubiks);
void coincoin(Face* rubiks);
void change_coin2(Face* rubiks);
void right_move(Face* rubiks);
void left_move(Face* rubiks);
void mauv(Face* rubiks);
void couronne_2(Face* rubiks);
void test_croix_jaune(Face* rubiks);
void croix_jaune(Face* rubiks);
void test_L(Face* rubiks);
void test_barre(Face* rubiks);
void test_coin(Face* rubiks);
void bienplacerlescoins(Face* rubiks);
void interface();
#endif //PROJET_C_RUBIKS_H