/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:37:47 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/29 14:29:31 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)// return current time in miliseconds
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)//max - min
{
	return (pres - past);
}

void	action_print(t_rules *rules, int id, char *string)
{	
	// pthread_mutex_lock(&(rules->writing));
	if (!(rules->dieded))
	{
		// printf("%lli ", timestamp() - rules->first_timestamp);//total amount of time lock
		// printf("%i ", id);
		// printf("%s\n", string);
		printf("%lli %i %s\n", timestamp() - rules->philosophers[id - 1].creation_time, id, string);//total amount of time lock
	}
	// pthread_mutex_unlock(&(rules->writing));
	return ;
}

void	smart_sleep(long long time, t_rules *rules)
{
	long long i;

	i = timestamp();
	while (!(rules->dieded))
	{
		if (time_diff(i, timestamp()) >= time)//10 - 10 = 0 > 50 - 10 = 40, 90 - 10 = 80 >= time(50)
			break ;
		usleep(1000);
	}
}

int			ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}