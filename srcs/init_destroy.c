/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:24:06 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/17 15:52:18 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	error_mutex(t_table **table, int i, int j)
{
	while (--i)
	{
		if (pthread_mutex_destroy(&(*table)->phi[i].l_fork) != 0)
			ft_putstr_fd("Error: mutex_destroy\n", STDERR_FILENO);
	}
	if (j != 0)
	{
		if (j >= 1)
		{
			if (pthread_mutex_destroy(&(*table)->param.print) != 0)
				ft_putstr_fd("Error: mutex_destroy\n", STDERR_FILENO);
		}
		if (j >= 2)
		{
			if (pthread_mutex_destroy(&(*table)->param.end) != 0)
				ft_putstr_fd("Error: mutex_destroy\n", STDERR_FILENO);
		}
		if (j >= 3)
		{
			if (pthread_mutex_destroy(&(*table)->param.death) != 0)
				ft_putstr_fd("Error: mutex_destroy\n", STDERR_FILENO);
		}
	}
	free((*table)->phi);
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->param.nb_phi)
	{
		if (pthread_mutex_destroy(&table->phi[i].l_fork) != 0)
			ft_putstr_fd("Error: mutex_destroy\n", STDERR_FILENO);
		i++;
	}
	if (pthread_mutex_destroy(&table->param.end) != 0)
		ft_putstr_fd("Error: mutex_destroy\n", STDERR_FILENO);
	if (pthread_mutex_destroy(&table->param.print) != 0)
		ft_putstr_fd("Error: mutex_destroy\n", STDERR_FILENO);
	if (pthread_mutex_destroy(&table->param.death) != 0)
		ft_putstr_fd("Error: mutex_destroy\n", STDERR_FILENO);
	free(table->phi);
}

static void	ft_init_val(t_table **table, int i)
{
	(*table)->phi[i].arg = &(*table)->param;
	(*table)->phi[i].id = i + 1;
	(*table)->phi[i].nb_meal = 0;
	(*table)->phi[i].eating = 0;
	(*table)->phi[i].last_meal = 0;
}

void	ft_init_lst(t_table *table)
{
	int		i;

	i = 0;
	table->phi = malloc(sizeof(t_philo) * table->param.nb_phi);
	if (!table->phi)
		return (ft_putstr_fd("Error: malloc\n", STDERR_FILENO));
	while (i < table->param.nb_phi - 1)
	{
		ft_init_val(&table, i);
		table->phi[i].r_fork = &table->phi[i + 1].l_fork;
		if (pthread_mutex_init(&table->phi[i].l_fork, NULL) != 0)
		{
			ft_putstr_fd("Error: mutex_init\n", STDERR_FILENO);
			return (error_mutex(&table, i, 0));
		}
		i++;
	}
	ft_init_val(&table, i);
	table->phi[i].r_fork = &table->phi[0].l_fork;
	if (pthread_mutex_init(&table->phi[i].l_fork, NULL) != 0)
	{
		ft_putstr_fd("Error: mutex_init\n", STDERR_FILENO);
		return (error_mutex(&table, i, 0));
	}
}
