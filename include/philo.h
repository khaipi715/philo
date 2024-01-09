/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:30:28 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/05 15:15:35 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTORY,
	CREATE,
	DETACH,
}	t_opcode;

typedef pthread_mutex_t	t_mtx;

typedef	struct s_table	t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
	int			id;
	long		meals;
	bool		full;
	bool		last_meal;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	long	philo_nbr;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	long	limit_meals;
	bool	t_start;
	bool	t_end;
	t_fork	*forks;
	t_philo	*philos;
}			t_table;

// parsing
void	parse_input(t_table *table, char **av);

// utils
long	ft_atol(const char *str);
void	error_exit(const char *error);
void	data_init(t_table *table);

// others
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);

#endif
