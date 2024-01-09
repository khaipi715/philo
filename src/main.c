/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:53:54 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/05 12:13:55 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int ac, char const *av[])
{
	t_table	table;
	if (ac != 5 && ac != 6)
		error_exit("wrong agument");
	else
	{
		parse_input(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	
	return 0;
}
