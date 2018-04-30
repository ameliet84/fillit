#include "fillit.h"


int test_tab1(char **tab, int i, int j, int size)
{
	int l;

	l = -1;
	while(++l <  2 && j + l<size)
		if(tab[i][j+l] == '.')
			return 1;
	return 0;
}

int test_tab2(char **tab, int i, int j, int size)
{
	int l;

	l = -1;
	while(++l <  2 && i + l<size)
		if(tab[i+l][j] == '.')
			return 1;
	return 0;
}


int ligne(char **tab, int i, int j)
{
	int count;

	count = 0;
	--j;
	while(++j < 4)
		if(tab[i][j]!='.')
			++count;
//			count=(tab[i][j].car!='.')? k-j+1:k-j;
	return count;
}

int colonne(char **tab, int i, int j)
{
	int count;

	count = 0;
	--i;
	while(++ i <4)
		if(tab[i][j] != '.')
			++count;
	//		count=(tab[i][j].car =='.')? k - i : k- i + 1;
	return count;
}

void coord( t_piece *piece, int i, int j, int k)
{
	if(k == 0)
	{
		piece->coord1x = i;
		piece->coord1y = j;
//	printf("piece coord1x = %d, i = %d\n", piece.coord1x, i);
//	printf("piece coord1y = %d, j = %d\n", piece.coord1y, j);

	}
	else if(k == 1)
	{
		piece->coord2x = i;
		piece->coord2y = j;
//	printf("piece coord2x = %d, i = %d\n", piece.coord2x, i);
//	printf("piece coord2y = %d, j = %d\n", piece.coord2y, j);

	}
	else if(k == 2)
	{
		piece->coord3x = i;
		piece->coord3y = j;
//	printf("piece coord3x = %d, i = %d\n", piece.coord3x, i);
//	printf("piece coord3y = %d, j = %d\n", piece.coord3y, j);
	}
	else
	{
		piece->coord4x = i;
		piece->coord4y = j;
//	printf("piece coord4x = %d, i = %d\n", piece.coord4x, i);
//	printf("piece coord4y = %d, j = %d\n", piece.coord4y, j);
	}

}

void reduce_piece(char **tab, int initx, int inity)
{
	int i;
	int j;

	i = -1;
	while(++i<4)
	{
		j = -1;
		while(++j<4)
			tab[i][j]= (i+initx<4 && j+inity<4) ? tab[i+initx][j+inity] : '.';
	}
}

void coord2(char **tab, t_piece *piece)
{
	int i;
	int j;
	int k;
	t_coord max;

	i =-1;
	k = 0;
	max.x = 0;
	max.y = 0;
	while(++i<4)
	{
		j = -1;
		while(++j<4)
			if(tab[i][j]!='.')
			{
				if(i>max.x)
					max.x = i;
				if(j>max.y)
					max.y = j;
				coord(piece, i, j, k);
				++k;
			}
	}
	piece->maxi = max.x+1;
	piece->maxj = max.y+1;
}

void treat_trio2(char **tab, t_piece *piece)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(skip_lines(tab, i) == 1)
		++i;
	while(skip_cols(tab, j) == 1)
		++j;
	reduce_piece(tab, i, j);
	coord2(tab, piece);
}

int 	square(int nbr)
{
	int n;

	n=0;
	while(n*n<nbr)
		++n;
	return n;
}


void print_tab(char **tab, int size)
{
	int i;
	int j;

	i = -1;
	while(++i<size)
	{
		j = -1;
		while(++j<size)
		{
				write(1, &tab[i][j], 1);
		}
			write(1, "\n", 1);
	}
	write(1, "\n",1);
}


int test_trio2(char **tab, int i, int j)
{
	int nbr;

	nbr = 0;
	if(i>0 && tab[i-1][j] != '.') 
		++nbr;
	if(i<3 && tab[i+1][j] != '.')
		++nbr;
	if(j>0 && tab[i][j-1] != '.') 
		++nbr;
	if(j<3 && tab[i][j+1] != '.')
		++nbr;
	return nbr;
}

int test_trio(char **tab)
{
	int i;
	int j;
	int nbr;

	i = -1;
	nbr = 0;
	while(++i <4)
	{
		j = -1;
		while(++j<4)
			if((tab[i][j]!= '.' && test_trio2(tab, i, j) == 0))
				return 0;
			else if(tab[i][j]!= '.' && test_trio2(tab, i, j)>nbr)
				nbr = test_trio2(tab, i, j);
	}
	if(nbr == 1)
		return 0;
	return 1;
}


char **create_tab(int size)
{
	char **tab;
	int i;

	i = -1;
	tab = malloc(sizeof(char *)*size);
	while(++i<size)
		tab[i] = malloc(sizeof(char) * size);
	return tab;
}


int skip_lines(char **tab, int i)
{
	int j;
	
	j= -1;
	while(++j < 4)
		if (tab[i][j] != '.')
			return 0;
	return 1;	
}

int skip_cols(char **tab, int i)
{
	int j;
	

	j= -1;
	while(++j < 4)
		if (tab[j][i] != '.')
			return 0;
	return 1;	
}


int test_piece(char **table, t_piece piece, int i, int j)
{
	if( table[piece.coord1x+i][piece.coord1y + j] != '.')
		return 0;
	if( table[piece.coord2x+i][piece.coord2y + j] != '.')
		return 0;
	if( table[piece.coord3x+i][piece.coord3y + j] != '.')
		return 0;
	if( table[piece.coord4x+i][piece.coord4y + j] != '.')
		return 0;
	char a;

	a = piece.letter;
	table[piece.coord1x+i][piece.coord1y + j] = a;
	table[piece.coord2x+i][piece.coord2y + j] = a;
	table[piece.coord3x+i][piece.coord3y + j] = a;
	table[piece.coord4x+i][piece.coord4y + j] = a;
	return 1;
}




void init_table(char **table, int size)
{
	int i;

	i=-1;
	while(++i<size*size)
		table[i/size][i%size] = '.';
}

int length(char **tab)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while(tab[0][++i])
		j++;
	return j;
}

void remove_piece(char **table, t_piece piece, int i, int j)
{
	table[piece.coord1x+i][piece.coord1y + j] = '.';
	table[piece.coord2x+i][piece.coord2y + j] = '.';
	table[piece.coord3x+i][piece.coord3y + j] = '.';
	table[piece.coord4x+i][piece.coord4y + j] = '.';
}

