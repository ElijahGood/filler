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

static void	get_sign_and_size(t_fill *filler, char *line)
{
	get_next_line(0, &line);
	if (line[10] == '1')// && ft_strstr(line, "inazarin"))
		(PLA = 'O');
	else
		(PLA = 'X');
	if (PLA == 'O')
		(OPP = 'X');
	else
		(OPP = 'O');
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

static void	init_struct(t_fill *filler, int flag)
{
	if (flag == 0)
	{
		M_X = 0;
		M_Y = 0;
		P_Y = 0;
		P_X = 0;
	}
	P_POS_Y = -1;
	P_POS_X = -1;
	P_MAX_Y = 0;
	P_MAX_X = 0;
	filler->put_y = 0;
	filler->put_x = 0;
	filler->dist_sum = 0;
	filler->highest_pos_pla = 101;
	filler->highest_pos_opp = 101;
	filler->high_put = -1;
	filler->high = -1;
	filler->match = 0;
}

static void	free_map_n_piece(t_fill *filler)
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

int			main(void)
{
	char	*line;
	t_fill	filler;

// open("map", O_CREAT | O_WRONLY | O_TRUNC, 0644);

	line = NULL;
	init_struct(&filler, 0);
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
			ft_printf("%d %d\n", filler.put_y, filler.put_x);
			free_map_n_piece(&filler);
			init_struct(&filler, 1);
		}
	}
}
