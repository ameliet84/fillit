#include "fillit.h"

int read_trios(t_piece piece[26], char **tab, int fd)
{
	char str[20];
	int k;
	int i;
	int n;
	int j;

	k = 0;
	while(read(fd, str, 20) > 0)
	{
		n =0;
		i = -1;
		j = 0;
		while(++i<19)
		{
			if(((i+1)%5 == 0 && str[i] != '\n' )|| ((i+1)%5 != 0 && str[i] != '.' && str[i] != '#'))
				return 0;
			else if((i+1)%5 == 0)
			{
				++j;
				++i;
			}
			if(str[i] == '#')
				++n;
			tab[(i-j)/4][(i-j)%4] = str[i];
		}
		if(n != 4 || test_trio(tab) == 0 || (read(fd, str, 1) >0 && str[0] != '\n'))
			return 0;
		treat_trio2(tab, &piece[k]);
		piece[k].letter = 'A' + k;
		++k;
	}
	return k;
}

int fill_tab(char **table, t_piece piece[26], int k, int len)
{
	int i;
	int j;
	int maxi;
	int maxj;

	maxi = piece[k].maxi;
	maxj = piece[k].maxj;
	i = -1;
	if(k == piece[0].size)
		return 1;
	while(++i <= len - maxi)
	{
		j = -1;
		while(++j <= len - maxj)
		{	
			if( test_piece(table, piece[k], i, j) == 1)
			{
				place_piece(table, piece[k], i, j);
				if(fill_tab(table, piece, k+1, len) == 1)
					return 1;
				remove_piece(table, piece[k], i, j);
			}
		}
	}
	return 0;
}
/*
int fill_tab(char **table, t_piece ***tab, int k)
{
	int i;
	int j;
	int maxi;
	int maxj;
	int size;
	int len;

	len = length(table);
	size = tab[0][0][0].size;
	t_coord init[26];

	i = -1;
	while(++i<26)
	{
		init[i].x = -1;
		init[i].y = -1;
	}
	while(k<size)
	{
		i = init[k].x;
		maxi = tab[k][0][0].maxi;
		maxj = tab[k][0][0].maxj;
		while(++i<=len - maxi)
		{
			j = init[k].y;
			while(++j <= len - maxj)
			{
				if(test_piece(table, tab[k], i, j) == 1)
					place_piece(table, tab[k], i, j);
					init[k].x = i;
					init[k].y = j;
					++ k;
					if(k == size)
						return 1;
					init[k].x = -1;
					init[k].y = -1;
					j = len;
			}
		}
		if(k==0)
			return 0;
		--k;
		if(init[k].y == len - maxj)
		 	init[k].y = -1;
		 else
		 	--init[k].x;
	}
	return 1;
}
*/

void fill_it(t_piece piece[26], int size)
{
	char **table;
	int len;
	int i;

	i = 0;
	len = square((size)*4);
	table = create_tab(len);
	init_table(table, len);
	while(fill_tab(table, piece, 0, len)==0)
	{
		free(table);
		printf("square = %d et size = %d\n",square((size+i)*4), size);
		++i;
		len = square((size+i)*4);
		table = create_tab(len);
		init_table(table, len);
	}
		print_tab(table, len);
		free(table);
}

int main(int argc, char **argv)
{
	int test;
	char **tab;
	int i;
	t_piece piece[26];

	i =-1;
	tab=malloc(sizeof(char*)*4);
	while(++i<4)
		tab[i] = malloc(sizeof(char)*4);
	test = (argc == 2) ? read_trios(piece, tab, open(argv[1], O_RDONLY)): read_trios(piece, tab, 0);
	free(tab);		
	if(test == 0)
		write(1, "error\n", 6);
	else
	{
		i = -1;
		while(++i<test)
			piece[i].size = test;
		fill_it(piece, test);
	}
	return 0;
}