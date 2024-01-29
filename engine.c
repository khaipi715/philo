/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:35:54 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/29 14:38:03 by lnaulak          ###   ########.fr       */
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
//		usleep(1000);
	else
		philo->state = 's';
	philo->creation_time = timestamp();
	while (1)
	{
		// 1 E
		// 3 T
		//pthread_mutex_lock(&rules->read_fork);
		pthread_mutex_lock(&rules->forks[philo->left_fork_id]);
		pthread_mutex_lock(&rules->forks[philo->right_fork_id]);
		mine_avail = rules->avail[philo->right_fork_id];
		next_avail = rules->avail[philo->left_fork_id];
		// pthread_mutex_unlock(&rules->read_fork);
		if (philo->state == 's')
		{
			pthread_mutex_unlock(&rules->forks[philo->left_fork_id]);
			pthread_mutex_unlock(&rules->forks[philo->right_fork_id]);
			//pthread_mutex_unlock(&rules->read_fork);
			action_print(rules, philo->id, "is sleeping");
			smart_sleep(rules->time_tsleep, rules);
			philo->state = 'e';
		}
		else if (philo->state == 'e' && (mine_avail && next_avail))
		{
			// pthread_mutex_lock(&rules->read_fork);
			//printf("%d %d\n", philo->right_fork_id, philo->left_fork_id);
			rules->avail[philo->right_fork_id] = false;
			rules->avail[philo->left_fork_id] = false;
			//pthread_mutex_unlock(&rules->read_fork);
			pthread_mutex_unlock(&rules->forks[philo->left_fork_id]);
			pthread_mutex_unlock(&rules->forks[philo->right_fork_id]);
			
			action_print(rules, philo->id, "is eating");
			smart_sleep(rules->time_teat, rules);
			pthread_mutex_lock(&rules->forks[philo->left_fork_id]);
			pthread_mutex_lock(&rules->forks[philo->right_fork_id]);
//			pthread_mutex_lock(&rules->read_fork);
			rules->avail[philo->right_fork_id] = true;
			rules->avail[philo->left_fork_id] = true;
//			pthread_mutex_unlock(&rules->read_fork);
			pthread_mutex_unlock(&rules->forks[philo->left_fork_id]);
			pthread_mutex_unlock(&rules->forks[philo->right_fork_id]);
			philo->state = 's';
			// pthread_mutex_unlock(rules->fork[philo->left_fork_id]);//for last philo it need to wait for first philo to be unlock
			// pthread_mutex_unlock(rules->fork[philo->right_fork_id - 1]);
			philo->print_think = false;
		}
		else
		{
			// static int dddd = 0;

			// dddd++;
			// if (dddd % 100 == 0)
			// 	printf("%d %c %d %d\n", philo->id, philo->state, mine_avail, next_avail);
			// pthread_mutex_unlock(&rules->read_fork);
			pthread_mutex_unlock(&rules->forks[philo->left_fork_id]);
			pthread_mutex_unlock(&rules->forks[philo->right_fork_id]);
			// if (philo->print_think == false)
			// 	philo->think_timer = timestamp();
			// if (philo->think_timer - timestamp() > 3)
			// 	action_print(rules, philo->id, "is thinking");
			if (philo->print_think == false)
				action_print(rules, philo->id, "is thinking");
			philo->print_think = true;
		}
		usleep(100);
		
		// if (i % 2 == 1)//if philo id is odd
		// {
		// 	pthread_mutex_lock(rules->fork[philo->left_fork_id]);//for last philo it need to wait for first philo to be unlock
		// 	pthread_mutex_lock(rules->fork[philo->right_fork_id - 1]);
		// 	if (philo->id == rules->nb_philo)
		// 		action_print(rules, philo->id, "is thinking");
		// 	action_print(rules, philo->id, "is eating");
		// 	smart_sleep(rules->time_teat, rules);
		// 	pthread_mutex_unlock(rules->fork[philo->left_fork_id]);//for last philo it need to wait for first philo to be unlock
		// 	pthread_mutex_unlock(rules->fork[philo->right_fork_id - 1]);
		// }
		// else
		// {
		// 	action_print(rules, philo->id, "is sleeping");
		// 	smart_sleep(rules->time_tsleep, rules);
		// }
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