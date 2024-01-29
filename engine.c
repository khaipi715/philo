/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:35:54 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/29 14:56:14 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_creation(void *philo_ptr)
{
	t_rules			*rules;
	t_philosopher *const	philo = (t_philosopher *)philo_ptr;
	bool			mine_avail;
	bool			next_avail;

	rules = philo->rules;
	if (philo->id % 2 != 0)
	{
		philo->state = 'e';
	}
	else
		philo->state = 's';
	philo->creation_time = timestamp();
	while (1)
	{
		pthread_mutex_lock(&rules->read_fork);
		mine_avail = rules->avail[philo->right_fork_id];
		next_avail = rules->avail[philo->left_fork_id];
		if (philo->state == 's')
		{
			pthread_mutex_unlock(&rules->read_fork);
			action_print(rules, philo->id, "is sleeping");
			smart_sleep(rules->time_tsleep, rules);
			philo->state = 'e';
			usleep(100);
		}
		else if (philo->state == 'e' && (mine_avail && next_avail))
		{
			rules->avail[philo->right_fork_id] = false;
			rules->avail[philo->left_fork_id] = false;
			pthread_mutex_unlock(&rules->read_fork);
			action_print(rules, philo->id, "is eating");
			smart_sleep(rules->time_teat, rules);
			pthread_mutex_lock(&rules->read_fork);
			rules->avail[philo->right_fork_id] = true;
			rules->avail[philo->left_fork_id] = true;
			pthread_mutex_unlock(&rules->read_fork);
			philo->state = 's';
			philo->print_think = false;
		}
		else
		{
			pthread_mutex_unlock(&rules->read_fork);
			if (philo->print_think == false)
				action_print(rules, philo->id, "is thinking");
			philo->print_think = true;
		}
		usleep(100);
	}
	return (NULL);
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
		pthread_create(&philo[i].thread_id, NULL, &thread_creation, &rules->philosophers[i]);
		i++;
	}
	sleep(10000);
	// while (true)
	// {
	// 	i = 0;
	// 	while (i < rules->nb_philo)
	// 	{
	// 		if (rules->philosophers[i].state == 'd')
	// 			return 0;
	// 		i++;
	// 	}
	// } 
	return (0);
}