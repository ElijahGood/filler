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
	int				p_pos_y;
	int				p_pos_x;
	int				put_y;
	int				put_x;
}					t_fill;

#include "./libft/libft.h"

#endif