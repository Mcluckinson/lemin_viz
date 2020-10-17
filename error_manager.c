/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:58:09 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:58:13 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"

bool		check_ants_quantity(int quantity, char *line)
{
	char	*checker;

	checker = NULL;
	if (quantity <= 0)
		return (false);
	checker = ft_itoa(quantity);
	if (!ft_strequ(checker, line))
	{
		free(checker);
		return (false);
	}
	free(checker);
	return (true);
}
