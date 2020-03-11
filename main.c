/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:27:38 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/11 19:36:11 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_viz.h"


static int 		read_data(t_all_data *data)
{
	if (!read_ants(data))
		return (0);
	if (!read_rooms(data))
		return (0);
	if (!data->start || !data->end)
		return (0);
	if (!read_links(data))
		return (0);
	if (!read_steps(data))
		return (0);
	return (1);
}
///////////dont forget to delete em args he he
int main(int ac, char **av)
{
	t_all_data *data;

	data = NULL;
	if (!(data = (t_all_data*)ft_memalloc(sizeof(t_all_data))))
		return (0);
	///////////del this one below
	data->del_me_fd = open(av[1], O_RDONLY);
	if (!(read_data(data)))
		printf("TI PIDOR\n");
	else
		printf("TI KOROL\n");
	return (0);
//		free_and_quit(data);

}