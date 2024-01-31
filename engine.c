/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:35:54 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/31 14:56:07 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_creation(void *philo_ptr)
{
	t_rules					*rules;
	t_philosopher *const	philo = (t_philosopher *)philo_ptr;

	rules = philo->rules;
	if (philo->id % 2 != 0)
		philo->state = 'e';
	else
		philo->state = 's';
	philo->creation_time = timestamp();
	philo->t_last_meal = philo->creation_time;
	while (1)
		if (threads(rules, philo) == 0)
			return (NULL);
	return (NULL);
}

int	death_checker(t_rules *rules)
{
	t_philosopher	*philo;
	int				i;

	philo = rules->philosophers;
	while (true)
	{
		i = 0;
		while (i < rules->nb_philo)
		{
			if (philo->t_last_meal + philo->rules->time_tdeath < timestamp())
			{
				action_print(rules, i + 1, "died");
				pthread_mutex_lock(&rules->dieded_lock);
				rules->dieded = true;
				pthread_mutex_unlock(&rules->dieded_lock);
				return (0);
			}
			i++;
		}
	}
}

int	exit_launcher(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	// printf("mutex destory success\n");
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philosophers[i].thread_id, NULL);
		i++;
	}
	i = 0;
	// printf("thread destory success\n");
	pthread_mutex_destroy(&rules->dieded_lock);
	pthread_mutex_destroy(&rules->read_fork);
	free(rules->avail);
	free(rules->philosophers);
	free(rules->forks);
	return (0);
}

int	engine(t_rules *rules)
{
	t_philosopher	*philo;
	int				i;

	philo = rules->philosophers;
	i = 0;
	rules->first_timestamp = timestamp();
	while (i < rules->nb_philo)
	{
		philo->t_last_meal = timestamp();
		pthread_create(&philo[i].thread_id, NULL,
			&thread_creation, &rules->philosophers[i]);
		i++;
	}
	if (death_checker(rules) == 0)
	{
		exit_launcher(rules);
		return (0);
	}
	return (0);
}
