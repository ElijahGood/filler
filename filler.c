/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 10:58:45 by inazarin          #+#    #+#             */
/*   Updated: 2018/05/22 10:58:47 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>

static void	get_sign_and_size(t_fill	*filler, char *line)
{
	get_next_line(0, &line);
	(line[10] == '1') ? (PLA = 'O') : (PLA = 'X');
	(PLA == 'O') ? (OPP = 'X') : (OPP = 'O');
	free(line);
	get_next_line(0, &line);
	if (ft_strstr(line, "Plateau"))
	{
		if (ft_strstr(line, "100"))
		{
			M_Y = ft_atoi(&line[8]);
			M_X = ft_atoi(&line[12]);
		}
		else
		{
			M_Y = ft_atoi(&line[8]);
			M_X = ft_atoi(&line[11]);
		}
	}
	free(line);
}

static void	init_struct(t_fill	*filler)
{
	M_X = 0;
	M_Y = 0;

	P_Y = 0;
	P_X = 0;
	filler->put_y = 0;
	filler->put_x = 0;
	filler->dist_sum = 0;
}

static void		get_piece(t_fill *filler, char *line)
{
	int j;
	int i;

	i = 0;
	P_Y = ft_atoi(&line[6]);
	P_X = ft_atoi(&line[8]);
	PIECE = (int **)malloc(sizeof(int *) * (P_Y + 1));
	free(line);
	while (i < P_Y)
	{
		j = -1;
		PIECE[i] = (int *)malloc(sizeof(int) * (P_X + 1));
		ft_bzero(PIECE[i], P_X + 1);
		get_next_line(0, &line);
		while (++j < P_X)
		{
			if (line[j] == '.')
				PIECE[i][j] = 0;
			else if (line[j] == '*')
				PIECE[i][j] = 1;
		}
		PIECE[i][j] = '\0';
		free(line);
		i++;
	}
	PIECE[i] = NULL;
}
// static void		get_plateau(t_fill *filler, char *line)
// {

// }

static void		magic(t_fill *filler, int i, int j, int k)
{
	k++;
	if (i > 0 && MAP[i - 1][j] == 0)
		MAP[i - 1][j] = k;
	if (j > 0 && MAP[i][j - 1] == 0)
		MAP[i][j - 1] = k;
	if (i < (M_Y - 1) && MAP[i + 1][j] == 0)
		MAP[i + 1][j] = k;
	if (j < (M_X - 1) && MAP[i][j + 1] == 0)
		MAP[i][j + 1] = k;
	//test mb its too much
	if (i < (M_Y - 1) && j < (M_X - 1) && MAP[i + 1][j + 1] == 0) 
		MAP[i + 1][j + 1] = k;
	if (i > 0 && j > 0 && MAP[i - 1][j - 1] == 0)
		MAP[i - 1][j - 1] = k;
	if (i > 0 && j < (M_X - 1) && MAP[i - 1][j + 1] == 0)
		MAP[i - 1][j + 1] = k;
	if (j > 0 && i < (M_Y - 1) && MAP[i + 1][j - 1] == 0)
		MAP[i + 1][j - 1] = k;
}

static void 	modify_plateau(t_fill *filler)
{
	int			i;
	int			j;
	int			k;

	k = -1;
	while (++k < (M_Y + M_X))
	{
		i = -1;
		while (++i < M_Y)
		{
			j = -1;
			while (++j < M_X)
			{
				if (MAP[i][j] == -1 && k == 0)
					magic(filler, i, j, k);
				else if (k > 0 && MAP[i][j] == k)
					magic(filler, i, j, k);
			}
		}
	}
}

static void		get_plateau(t_fill *filler, char *line)
{
	int			i;
	int			j;

	i = -1;
	free(line);
	MAP = (int **)malloc(sizeof(int *) * (M_Y + 1));
	while (++i < M_Y)
	{
		j = -1;
		MAP[i] = (int *)malloc(sizeof(int)*(M_X + 1));
		ft_bzero(MAP[i], M_X + 1);
		get_next_line(0, &line);
		while (++j < M_X)
		{
			if (line[4 + j] == '.')
				MAP[i][j] = 0;
			else if (((line[4 + j] == 'X' || line[4 + j] == 'x') && PLA == 'X')
				|| ((line[4 + j] == 'O' || line[4 + j] == 'o') && PLA == 'O'))
				MAP[i][j] = -2;
			else if (((line[4 + j] == 'O' || line[4 + j] == 'o') && OPP == 'O')
				|| ((line[4 + j] == 'X' || line[4 + j] == 'x') && OPP == 'X'))
				MAP[i][j] = -1;
		}
		MAP[i][j] = '\0';
		free(line);
	}
	MAP[i] = NULL;
}
/*
static void	save_plateau(t_fill *filler)
{
	int 	i = 0;
	int 	j = 0;

	dprintf(3, "\nmy Map[%d,%d]\n", M_Y, M_X);
	while (i < M_Y) //map check
	{
		j = 0;
		while (j < M_X)
		{
			dprintf(3, "%3d", MAP[i][j]);
			j++;
		}
		dprintf(3, "\n");
		i++;
	}
}

static void	save_piece(t_fill *filler)
{
	int 	i = 0;
	int 	j = 0;

	dprintf(3, "my piece[%d,%d]\n", P_Y, P_X);
	while (i < P_Y)
	{
		j = 0;
		while (j < P_X)
		{
			dprintf(3, "% d", PIECE[i][j]);
			j++;
		}
		dprintf(3, "\n");
		i++;
	}
}
*/
// static int		check_piece_on_map(t_fill *filler, int y, int x)
// {
// 	int 	i;

// 	i = -1;
// 	while (++i < P_Y)
// 	{
// 		j = -1;
// 		while (++j < P_X)
// 		{
// 			if (PIECE[i][j] == 1 && MAP[i + y][j + x] == -1)
// 				return (0);
// 		}
// 	}
// 	return (1);
// }

static void		check_piece_place(t_fill *filler, int y, int x)
{	
	int		i;
	int		j;
	int		match;
	int		sum;

	sum = 0;
	i = 0;
	match = 0;
	while (i < P_Y)
	{
		j = 0;
		while (j < P_X)
		{
			if (MAP[y + i][x + j] != -2 && MAP[y + i][x + j] != -1)
				sum += MAP[y + i][x + j];
			if (PIECE[i][j] == 1 && MAP[y + i][x + j] == -2
				&& MAP[y + i][x + j] != 'X' && MAP[y + i][x + j] != 'x') 
				match++;
			if ((PIECE[i][j] == 1 && MAP[y + i][x + j] == -1) || match > 1)
				return ;
			j++;
		}
		i++;
	}
	if (match == 1 && (sum < filler->dist_sum || filler->dist_sum == 0))//fix that fuck!
	{
		filler->dist_sum = sum;
		filler->put_x = x;
		filler->put_y = y;
	}
}

static void 	place_piece(t_fill *filler)
{
	int		y;
	int		x;

	y = -1;
	while (++y <= (M_Y - P_Y))
	{
		x = -1;
		while (++x <= (M_X - P_X))
		{
			check_piece_place(filler, y, x);
		}
	}
}

static void	free_map_piece(t_fill *filler)
{
	int		i;

	i = 0;
	while (i < M_Y)
		free(MAP[i++]);
	free(MAP);
	i = 0;
	while (i < P_Y)
		free(PIECE[i++]);
	free(PIECE);
}

int main(void)
{
	char	*line;
	int		i;

	t_fill	filler;

	init_struct(&filler);
	i = 0;
	open("map", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	
	/* O or X figure out -- first line parsing */
	line = NULL;
	get_sign_and_size(&filler, line);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strstr(line, "0123456789"))
		{
			get_plateau(&filler, line);
			modify_plateau(&filler);
		}
		else if (ft_strstr(line, "Piece"))
		{
			get_piece(&filler, line);
			// save_plateau(&filler);
			// save_piece(&filler);
			place_piece(&filler);
			// dprintf(3, "puts: y= %d, x= %d\n", filler.put_y, filler.put_x);
			ft_printf("%d %d\n", filler.put_y, filler.put_x);
			free_map_piece(&filler);
			filler.put_y = 0;
			filler.put_x = 0;
			filler.dist_sum = 0;
		}
		// dprintf(3, "main while %s\n", line);
		// dprintf(3, "main while %p\n", (void *)line);
		// free(line);
	}
}
