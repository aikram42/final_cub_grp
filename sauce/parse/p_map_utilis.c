/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:47:56 by aikram            #+#    #+#             */
/*   Updated: 2023/11/24 22:28:11 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_start_zero(char **map, int j)
{
	int	i;

	i = 0;
	while (map[j])
	{
		if (map[j][i] == '1' || map[j][i] == '0')
			return (i);
		i++;
	}
	return (i);
}

int	check_map_is_at_the_end(t_imap *map)
{
	int	i;
	int	j;

	i = map->end_idx;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_map_elements(t_parse *parse, char **map_tab)
{
	int	i[2];

	i[0] = 0;
	parse->pdir = '0';
	while (map_tab[i[0]] != NULL)
	{
		i[1] = 0;
		while (map_tab[i[0]][i[1]])
		{
			while (parse->map[i[0]][i[1]] == ' ' \
			|| parse->map[i[0]][i[1]] == '\t' || parse->map[i[0]][i[1]] == '\r'
			|| parse->map[i[0]][i[1]] == '\v' || parse->map[i[0]][i[1]] == '\f')
				i[1]++;
			if (!(ft_strchr("10NSEW", map_tab[i[0]][i[1]])))
				return (print_err(parse->imap.path, "ERR_INV_LETTER", FAILURE));
			if (map_tab[i[0]][i[1]] && ft_strchr("NSEW", map_tab[i[0]][i[1]]) \
			&& parse->pdir != '0')
				return (print_err(parse->imap.path, "ERR_NUM_PLAYER", FAILURE));
			if (ft_strchr("NSEW", map_tab[i[0]][i[1]]) && parse->pdir == '0')
				set_plr_pos(parse, map_tab, i[0], i[1]);
			i[1]++;
		}
		i[0]++;
	}
	return (SUCCESS);
}

static int	ignore_spaces(t_parse *parse, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1])
			&& !ft_isdigit(map[i][j]))
		{
			if (fill_dir_tex(parse, map[i], j) == ERR)
				return (print_err(parse->imap.path, "bad texture", FAILURE));
			return (BR);
		}
		else
		{
			if (fill_color_textures(parse, map[i], j) == ERR)
				return (FAILURE);
			return (BR);
		}
	}
	else if (ft_isdigit(map[i][j]))
	{
		if (create_map(parse, map, i) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	return (CONTINUE);
}

int	get_map(t_parse *parse, char **map)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ret = ignore_spaces(parse, map, i, j);
			if (ret == BR)
				break ;
			else if (ret == FAILURE)
				return (FAILURE);
			else if (ret == SUCCESS)
				return (SUCCESS);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
