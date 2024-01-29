/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:30:58 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/29 14:29:02 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>

struct s_rules;

typedef	struct			s_philosopher
{
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	long long			creation_time;
	bool				print_think;
	char				state;
	struct s_rules		*rules;
	pthread_t			thread_id;
	struct t_rules 			*ruleset;
	//t_philosopher 		*right; // the philosopher to the right of me.
	//t_philosopher		*left; // the philosopher to the next of me.
}						t_philosopher;

typedef struct			s_rules
{
	int					nb_philo;
	int					time_tdeath;
	int					time_teat;
	int					time_tsleep;
	int					nb_to_eat;
	int					dieded;
	int					all_ate;
	int					lock;
	long long			first_timestamp;
	pthread_mutex_t		*forks;
	bool				*avail; // Are the forks available?
	pthread_mutex_t		writing;
	pthread_mutex_t		read_fork;
	t_philosopher		*philosophers;
}						t_rules;

/*
** ----- error_manager.c -----
*/

int						write_error(char *str);
int						error_manager(int error);

/*
** ----- init.c -----
*/

int						init_all(t_rules *rules, char **argv);

/*
** ----- utils.c -----
*/

int						ft_atoi(const char *str);
void					action_print(t_rules *rules, int id, char *string);
long long				timestamp(void);
long long				time_diff(long long past, long long pres);
void					smart_sleep(long long time, t_rules *rules);

/*
** ----- launcher.c -----
*/

int						engine(t_rules *rules);
void					exit_launcher(t_rules *rules, t_philosopher *philos);

#endif