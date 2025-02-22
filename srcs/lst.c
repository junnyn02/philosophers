/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:24:06 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/24 17:23:46 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philo	*ft_lstnew(int position)
{
	t_philo	*element;

	element = malloc(sizeof(t_philo));
	if (!element)
		return (NULL);
	element->id = position;
	return (element);
}

void	ft_init_lst(t_table *table)
{
	int		i;

	i = 0;
	table->phi = malloc(sizeof(t_philo) * table->param.nb_phi);
	if (!table->phi)
		return ;
	while (i < table->param.nb_phi - 1)
	{
		table->phi[i].arg = &table->param;
		table->phi[i].id = i + 1;
		table->phi[i].finish = 0;
		table->phi[i].eating = 0;
		table->phi[i].last_meal = 0;
		table->phi[i].r_fork = &table->phi[i + 1].l_fork;
		pthread_mutex_init(&table->phi->l_fork, NULL);
		i++;
	}
	table->phi[i].arg = &table->param;
	table->phi[i].id = i + 1;
	table->phi[i].finish = 0;
	table->phi[i].last_meal = 0;
	table->phi[i].eating = 0;
	table->phi[i].r_fork = &table->phi[0].l_fork;
	pthread_mutex_init(&table->phi->l_fork, NULL);
}
