/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 17:49:05 by inazarin          #+#    #+#             */
/*   Updated: 2018/05/30 17:49:08 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		write_ret_nums(t_fill *filler, int sum, int y, int x)
{
	filler->dist_sum = sum;
	filler->put_x = x - P_POS_X;
	filler->put_y = y - P_POS_Y;
	dprintf(3, "PUTS: %d, %d, sum= %d\n", filler->put_y, filler->put_x, filler->dist_sum);
}


static void		check_piece_place(t_fill *filler, int y, int x)
{
	int			i;
	int			j;
	int			match;
	int			sum;

	sum = 0;
	match = 0;
	i = P_POS_Y - 1;
	while (++i < P_Y)
	{
		j = P_POS_X - 1;
		while (++j < P_X)
		{
			if ((M_COR != -2) && (M_COR != -1) && y >= 0 && x >= 0)
				sum += M_COR;
			if (PIECE[i][j] == 1 && M_COR == -2 && M_COR != 'X' && M_COR != 'x')
				match++;
			if ((PIECE[i][j] == 1 && M_COR == -1) || match > 1)
				return ;
		}
	}
	if (match == 1 && (sum < filler->dist_sum || filler->dist_sum == 0))
		write_ret_nums(filler, sum, y, x);
}


static void		write_ret_nums2(t_fill *filler, int sum, int y, int x)
{
	filler->dist_sum = sum;
	filler->put_x = x;
	filler->put_y = y;
	dprintf(3, "PUTS: %d, %d, sum= %d\n", filler->put_y, filler->put_x, filler->dist_sum);
}

//# define M_COR MAP[y + i - P_POS_Y][x + j - P_POS_X]
// # define M_ROC MAP[y - i + P_MAX_Y][x - j + P_MAX_X]
static void		check_piece_place2(t_fill *filler, int y, int x)
{
	int			i;
	int			j;
	int			match;
	int			sum;

// dprintf(3, "CHECK: y= %d, x= %d\n", y, x);
	sum = 0;
	match = 0;
	i = P_POS_Y - 1;//mb smth wrong with them + it dosnt go forward first match!!!
	while (++i <= P_MAX_Y)
	{
		j = P_POS_X - 1;
		while (++j <= P_MAX_X)
		{
			// dprintf(3, "MAP[y.x.]= %d,%d\n", y - i + P_MAX_Y, x - j + P_MAX_X);
			if ((M_ROC != -2) && (M_ROC != -1) && y >= 0 && x >= 0)
				sum += M_ROC;
			if (PIECE[i][j] == 1 && M_ROC == -2)
				match++;
			if ((PIECE[i][j] == 1 && M_ROC == -1) || match > 1)
				return ;
		}
	}
	if (match == 1 && (sum < filler->dist_sum || filler->dist_sum == 0))
		write_ret_nums2(filler, sum, y, x);
}

static void		place_piece(t_fill *filler)
{
	int			y;
	int			x;

	if ((PLA == 'X' && M_Y < 40) || (PLA == 'O' && M_Y > 40))
	{
		y = M_Y - P_MAX_Y;
		while (--y >= 0)
		{
			x = M_X - P_MAX_X;
			while (--x >= 0)
				check_piece_place2(filler, y, x);
		}
	}
	else
	{
		y = -1;
		while (++y <= (M_Y - P_Y))
		{
			x = -1;
			while (++x <= (M_X - P_X))
				check_piece_place(filler, y, x);
		}
	}
}

static void		get_pos_piece(t_fill *filler, int i, int j, char *line)
{
	if (line[j] == '.')
		PIECE[i][j] = 0;
	else if (line[j] == '*')
	{
		PIECE[i][j] = 1;
		if (P_POS_Y == -1)
			P_POS_Y = i;
		if (P_POS_X == -1)
			P_POS_X = j;
		else if (j < P_POS_X)
			P_POS_X = j;
		if (i > P_MAX_Y || (i > 0 && P_MAX_Y == 0))
			P_MAX_Y = i;
		if (j > P_MAX_X || (j > 0 && P_MAX_X == 0))
			P_MAX_X = j;
	}
}
static void	save_plateau(t_fill *filler)
{
	int 	i = 0;
	int 	j = 0;
	dprintf(3, "\nmy Map[%d,%d]\n", M_Y, M_X);
	while (i < M_Y)
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

void			get_piece(t_fill *filler, char *line)
{
	int			j;
	int			i;

	save_plateau(filler);

	P_Y = ft_atoi(&line[6]);
	P_X = ft_atoi(ft_strchr(&line[6], ' ') + 1);
	PIECE = (int **)malloc(sizeof(int *) * (P_Y + 1));
	free(line);
	i = -1;
	while (++i < P_Y)
	{
		j = -1;
		PIECE[i] = (int *)malloc(sizeof(int) * (P_X + 1));
		ft_bzero(PIECE[i], P_X + 1);
		get_next_line(0, &line);
		while (++j < P_X)
			get_pos_piece(filler, i, j, line);
		PIECE[i][j] = '\0';
		free(line);
	}
	PIECE[i] = NULL;
	dprintf(3, "P_MAX_Y: %d, P_MAX_X: %d\n", P_MAX_Y, P_MAX_X);
	place_piece(filler);

}
