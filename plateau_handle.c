/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plateau_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 17:46:34 by inazarin          #+#    #+#             */
/*   Updated: 2018/05/30 17:46:40 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
	if (i < (M_Y - 1) && j < (M_X - 1) && MAP[i + 1][j + 1] == 0)
		MAP[i + 1][j + 1] = k;
	if (i > 0 && j > 0 && MAP[i - 1][j - 1] == 0)
		MAP[i - 1][j - 1] = k;
	if (i > 0 && j < (M_X - 1) && MAP[i - 1][j + 1] == 0)
		MAP[i - 1][j + 1] = k;
	if (j > 0 && i < (M_Y - 1) && MAP[i + 1][j - 1] == 0)
		MAP[i + 1][j - 1] = k;
}

void			modify_plateau(t_fill *filler)
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

static void		parce_positions(t_fill *filler, char *line, int i, int j)
{
	if (line[4 + j] == '.')
		MAP[i][j] = 0;
	else if (((line[4 + j] == 'X' || line[4 + j] == 'x') && PLA == 'X')
		|| ((line[4 + j] == 'O' || line[4 + j] == 'o') && PLA == 'O'))
	{
		MAP[i][j] = -2;
		(i < filler->highest_pos_pla) ? (filler->highest_pos_pla = i) : 0;
	}
	else if (((line[4 + j] == 'O' || line[4 + j] == 'o') && OPP == 'O')
		|| ((line[4 + j] == 'X' || line[4 + j] == 'x') && OPP == 'X'))
	{
		MAP[i][j] = -1;
		(i < filler->highest_pos_opp) ? (filler->highest_pos_opp = i) : 0;
	}
}

void			get_plateau(t_fill *filler, char *line)
{
	int			i;
	int			j;

	i = -1;
	free(line);
	MAP = (int **)malloc(sizeof(int *) * (M_Y + 1));
	while (++i < M_Y)
	{
		j = -1;
		MAP[i] = (int *)malloc(sizeof(int) * (M_X + 1));
		ft_bzero(MAP[i], M_X + 1);
		get_next_line(0, &line);
		while (++j < M_X)
		{
			parce_positions(filler, line, i, j);
		}
		MAP[i][j] = '\0';
		free(line);
	}
	MAP[i] = NULL;
}
