/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:14:31 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/05 12:44:47 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->t_die =  ft_atol(av[2]) * 1000;
	table->t_eat = ft_atol(av[3]) * 1000;
	table->t_sleep = ft_atol(av[4]) * 1000;
	if (table->t_die < 6e4
		|| table->t_eat < 6e4
		|| table->t_sleep < 6e4)
		error_exit("timestamp > 60ms");
	if (av[5])
		table->limit_meals = ft_atol(av[5]);
	else
		table->limit_meals = -1;
}