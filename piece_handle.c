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
	// dprintf(3, "PUTS: %d, %d, sum= %d\n", filler->put_y, filler->put_x, filler->dist_sum);
}

static void		check_piece_place(t_fill *filler, int y, int x, int sum)
{
	int			i;
	int			j;

	i = P_POS_Y - 1;
	while (++i < P_Y)
	{
		j = P_POS_X - 1;
		while (++j < P_X)
		{
			if ((M_COR != -2) && (M_COR != -1) && y >= 0 && x >= 0)
				sum += M_COR;
			if (PIECE[i][j] == 1 && M_COR == -2)
				filler->match++;
			if ((PIECE[i][j] == 1 && M_COR == -1) || filler->match > 1)
				return ;
		}
	}
	if (filler->match == 1 && (sum < filler->dist_sum || filler->dist_sum == 0))
		write_ret_nums(filler, sum, y, x);
}

static void		place_piece(t_fill *filler)
{
	int			y;
	int			x;
	// int			sum;

	// sum = 0;
	y = -1;
	while (++y <= (M_Y - P_Y))
	{
		x = -1;
		while (++x <= (M_X - P_X))
		{
			filler->high = -1;
			filler->match = 0;
			check_piece_place(filler, y, x, 0);
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
/*
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
		dprintf(3, "\nhighest_pos_opp= %d, highest_pos_pla= %d\n", filler->highest_pos_opp, filler->highest_pos_pla);

}
*/
void			get_piece(t_fill *filler, char *line)
{
	int			j;
	int			i;

	// save_plateau(filler);

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
	// dprintf(3, "P_MAX_Y: %d, P_MAX_X: %d\n", P_MAX_Y, P_MAX_X);
	place_piece(filler);

}
