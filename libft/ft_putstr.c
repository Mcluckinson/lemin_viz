/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:25:38 by cyuriko           #+#    #+#             */
/*   Updated: 2019/05/04 11:27:25 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *s)
{
	if (!s)
		return ;
	write(1, (unsigned const char*)s, ft_strlen(s));
}