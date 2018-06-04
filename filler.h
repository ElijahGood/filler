/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:23:51 by inazarin          #+#    #+#             */
/*   Updated: 2018/05/21 12:23:55 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "./libft/libft.h"

# define M_Y filler->map_y
# define M_X filler->map_x
# define P_Y filler->piece_one
# define P_X filler->piece_two
# define PLA filler->player_sign
# define OPP filler->opp_sign
# define MAP filler->map
# define PIECE filler->piece
# define P_POS_Y filler->p_pos_y
# define P_POS_X filler->p_pos_x
# define P_MAX_Y filler->p_max_y
# define P_MAX_X filler->p_max_x
# define M_COR MAP[y + i - P_POS_Y][x + j - P_POS_X]

typedef struct		s_fill
{
	int				map_x;
	int				map_y;
	char			player_sign;
	char			opp_sign;
	int				piece_one;
	int				piece_two;
	int				**piece;
	int				**map;
	int				dist_sum;
	int				highest_pos_pla;
	int				highest_pos_opp;
	int				high_put;
	int 			high;
	int				match;
	int				p_pos_y;
	int				p_pos_x;
	int				put_y;
	int				put_x;
	int				p_max_y;
	int				p_max_x;
}					t_fill;

void				get_piece(t_fill *filler, char *line);
void				modify_plateau(t_fill *filler);
void				get_plateau(t_fill *filler, char *line);

#endif
