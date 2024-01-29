/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:30:41 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/25 17:27:37 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

void		ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*lst;
	t_list	*prev;
	
	lst = *begin_list;
	prev = lst;
	while (lst)
	{
		if (0 == cmp(lst->data, data_ref))
			free(lst->data);
		lst = lst->next;
	}
}

void		ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list		*current;
	t_list		*previous;

	previous = 0;
	current = *begin_list;
	while (current)
	{
		if ((cmp)(current->data, data_ref) == 0)
		{
			if (previous == 0)
				*begin_list = current->next;
			else
				previous->next = current->next;
			free(current);//chatgtp say it's wrong but i should doulbe check
		}
		previous = current;
		current = current->next;
	}
}
