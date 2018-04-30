#ifndef FILLIT_H_
#define FILLIT_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>

typedef struct s_coord{
	int x;
	int y;
} t_coord;

typedef struct s_piece{
	char letter;
	int maxi;
	int maxj;
	int coord1x;
	int coord1y;
	int coord2x;
	int coord2y;
	int coord3x;
	int coord3y;
	int coord4x;
	int coord4y;
	int size;
}	t_piece;

#include "fillit.h"


int test_tab1(char **tab, int i, int j, int size);

int test_tab2(char **tab, int i, int j, int size);


int ligne(char **tab, int i, int j);

int colonne(char **tab, int i, int j);

void coord(t_piece *piece, int i, int j, int k);

void reduce_piece(char **tab, int initx, int inity);

void coord2(char **tab, t_piece *piece);

void treat_trio2(char **tab, t_piece *piece);

int 	square(int nbr);


void print_tab(char **tab, int size);

int test_trio2(char **tab, int i, int j);

int test_trio(char **tab);

char **create_tab(int size);


int skip_lines(char **tab, int i);

int skip_cols(char **tab, int i);

int test_piece(char **table, t_piece piece, int i, int j);

void init_table(char **table, int size);

int length(char **tab);

void remove_piece(char **table, t_piece piece, int i, int j);

void place_piece(char **table, t_piece piece, int i, int j);



#endif