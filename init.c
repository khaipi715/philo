/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:17:27 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/24 11:59:11 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_rules *rules)
{
	int				i;
	t_philosopher	*philo;
	t_philosopher	*prev;
	
	rules->philosophers = malloc(sizeof(t_philosopher) * rules->nb_philo);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	philo = rules->philosophers;
	i = 0;
	f = 0;
	while (i < rules->nb_philo)
	{
		philo[i].id = i + 1;
		f = i - 1;
		if (f < 0)
			f = rules->nb_philo - 1;
		philo[i].left_fork_id = f;
		philo[i].right_fork_id = i;
		philo[i].t_last_meal = 0;
		philo[i].x_ate = 0;
		philo[i].rules = rules;
	}
	return (0);
}

int	init_all(t_rules *rules, char **av)
{
	rules->nb_philo = ft_atoi(av[1]);
	rules->time_tdeath = ft_atoi(av[2]);
	rules->time_teat = ft_atoi(av[3]);
	rules->time_tsleep = ft_atoi(av[4]);
	if (rules->nb_philo < 2 || rules->time_tdeath < 0 || rules->time_teat < 0
		|| rules->time_tsleep < 0 || rules->nb_philo > 200)
		return (1);
	if (av[5] != NULL)
		rules->nb_teat = ft_atoi(av[5]);
	else
		rules->nb_teat = -1;
	//if (init_mutex(rules))
	//	return (2);
	init_philo(rules);
	return (0);
}