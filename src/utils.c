/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 21:02:38 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/14 16:43:22 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

int			del_line_and_return(char *line, int ret)
{
	if (ret || line)
		free(line);
	line = NULL;
	return (ret);
}

int			is_all_digits(char *line)
{
	int		i;

	i = -1;
	if (!line)
		return (0);
	while (line[++i])
	{
		if (line[i] >= '0' && line[i] <= '9')
			continue;
		else
			return (0);
	}
	return (1);
}

int			split_bits(char *line, char c)
{
	char	**split;
	int		i;
	int		j;

	i = -1;
	j = -1;
	split = NULL;
	if (!(split = ft_strsplit(line, c)))
		return (0);
	while (split[++i])
		continue ;
	while (split[++j])
		ft_strdel(&split[j]);
	free(split);
	return (i);
}

void		del_str_arr(char **to_delete)
{
	int		i;

	i = -1;
	if (to_delete)
	{
		while (to_delete[++i])
			ft_strdel(&to_delete[i]);
		free(to_delete);
	}
}

void		swap_values(int *a, int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
}
