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

int 	ft_error(const char *error)
{
	ft_putendl_fd(error, 2);
	exit(-1);
}

int 	del_line_and_return(char *line, int ret)
{
	free(line);
	line = NULL;
	return (ret);
}

int		is_all_digits(char *line)
{
	int i;

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

int 	split_bits(char *line, char e)
{
	char **split;
	int i;
	int c;

	c = -1;
	i = -1;
	split = NULL;
	if (!(split = ft_strsplit(line,  e)))
		return (0);
	while (split[++i])
		continue ;
	while (split[++c])
		ft_strdel(&split[c]);
	return (i);
}

void		del_str_arr(char **to_delete)
{
	int i;

	i = -1;
	if (to_delete)
	{
		while(to_delete[++i])
			ft_strdel(&to_delete[i]);
		free(to_delete);
	}
}