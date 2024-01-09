/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:50:53 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/05 14:34:38 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;
	
	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("malloc error");
	return (ret);
}

// mutex

static void handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		error_exit("cant create thread");	
	else if (status == EINVAL && (LOCK == opcode || UNLOCK == opcode))
		error_exit("mutex invalid");
	else if (EINVAL == status && INIT == opcode)
		error_exit("mutex invalid");
	else if (EDEADLK == status)
		error_exit("deadlock");
	else if (EPERM == status)
		error_exit("no lock mutex");
	else if (ENOMEN == status)
		error_exit("no memory for mutex");
	else if (EBUSY == status)
		error_exit("mutex lock");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else
		error_exit("wrong mutex");
}

// thread:

static void handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		error_exit("cant create thread");	
	else if (status == EINVAL && (LOCK == opcode || UNLOCK == opcode))
		error_exit("mutex invalid");
	else if (EINVAL == status && INIT == opcode)
		error_exit("mutex invalid");
	else if (EDEADLK == status)
		error_exit("deadlock");
	else if (EPERM == status)
		error_exit("no lock mutex");
	else if (ENOMEN == status)
		error_exit("no memory for mutex");
	else if (EBUSY == status)
		error_exit("mutex lock");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else
		error_exit("wrong mutex");
}