/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:35:56 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/18 12:20:36 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hyochoi_macros.h"

static int	parse_info(char *line, t_all *a)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
		
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (parse_tex(&line[i + 3], SOUTH, a));

	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (parse_tex(&line[i + 3], NORTH, a));

	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		return (parse_tex(&line[i + 3], EAST, a));

	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		return (parse_tex(&line[i + 3], WEST, a));

	else if (line[i] == 'S' && line[i + 1] == ' ')
		return (parse_tex(&line[i + 2], SPRITE, a));

	else if (line[i] == 'F' && line[i + 1] == ' ')
		return (parse_color(&line[i + 2], FLOOR, a));

	else if (line[i] == 'C' && line[i + 1] == ' ')
		return (parse_color(&line[i + 2], CEIL, a));

	else if (line[i] == 'R' && line[i + 1] == ' ')
		return (parse_resol(&line[i + 2], a));
		
	else
		return (INVALID_MAP);
}

static int	map_comp_check(t_all *a)
{
	int i;
	int j;
	int tmp;

	j = 0;
	while (a->map.map[j] != 0)
	{
		i = 0;
		while (a->map.map[j][i] != 0)
		{
			tmp = a->map.map[j][i];
			if (tmp == 'W' || tmp == 'E' || tmp == 'S' || tmp == 'N')
			{
				a->pl.pos_x = (double)i + 0.5;
				a->pl.pos_y = (double)j + 0.5;
				a->map.dir_init = tmp;
				a->map.pl_num++;
				if (a->map.pl_num > 1)
					return (MULTI_PLAYER);
			}
			if (!(tmp == ' ' || tmp == '0' || tmp == '1' || tmp == '2'
				|| tmp == 'W' || tmp == 'E' || tmp == 'S' || tmp == 'N'))
				return (INVALID_COMP);
			i++;
		}
		j++;
	}
	return (a->map.dir_init == 0 ? NO_PLAYER : 0);
}

static int	check_map(t_all *a)
{
	int		j;
	int		err;
	t_list	*cur;
	t_list	*next;

	j = 0;
	cur = a->map.list;
	while (is_blank_line(cur->content))
	{
		free(cur->content);
		next = cur->next;
		free(cur);
		cur = next;
	}
	a->map.h = ft_lstsize(cur);

	if (!(a->map.map = (char **)malloc(sizeof(char *) * (a->map.h + 1))))
		return (MALLOC_FAILED);

	while (j < a->map.h && (a->map.map[j++] = cur->content))
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	a->map.map[a->map.h] = 0;

	if ((err = map_comp_check(a)) != 0)
		return (err);
	if ((err = map_valid_check(a)) != 0)
		return (err);
	return (0);
}

static int	parse_line(char *line, t_all *a)
{
	int		err;
	t_list	*new;

	if (a->map.info_num != INFO_PARSED)
	{
		if (is_blank_line(line))
		{
			free(line);
			return (0);
		}
		if ((err = parse_info(line, a)) == 0)
			a->map.info_num += 1;
		free(line);
		return (err);
	}
	else
	{
		if ((new = ft_lstnew(line)) == 0)
			return (MALLOC_FAILED);
		ft_lstadd_back(&(a->map.list), new);
	}
	return (0);
}

int			parse_map(char *filename, t_all *a)
{
	int		fd;
	int		gnl_output;
	int		parse_output;
	int		err;
	char	*temp;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (OPEN_ERROR);
	while (1)
	{
		gnl_output = get_next_line(fd, &temp);

		if (gnl_output == -1)
			break ;

		parse_output = parse_line(temp, a);

		if (gnl_output == 0 || parse_output != 0)
			break ;
	}
	close(fd);

	if (gnl_output == -1)
		return (GNL_ERROR);
	else if (parse_output != 0 || a->map.info_num != INFO_PARSED)
		return (parse_output != 0 ? parse_output : LACKING_INFO);

	if ((err = check_map(a)))
		return (err);
	return (0);
}
