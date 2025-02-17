/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:58:04 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/17 16:57:42 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_end(t_philo *ph, int i)
{
	if (pthread_mutex_lock(&ph->arg->end) != 0)
		return (ft_putstr_fd("Error: mutex_lock", STDERR_FILENO), -1);
	if (i == 1)
		ph->arg->dead = 1;
	if (ph->arg->dead == 1 || ph->arg->finish == ph->arg->nb_phi)
	{
		if (pthread_mutex_unlock(&ph->arg->end) != 0)
			return (ft_putstr_fd("Error: mutex_unlock", STDERR_FILENO), -1);
		return (1);
	}
	if (pthread_mutex_unlock(&ph->arg->end) != 0)
		return (ft_putstr_fd("Error: mutex_unlock", STDERR_FILENO), -1);
	return (0);
}

void	*monitor(void *ph)
{
	t_philo	*phi;

	phi = (t_philo *)ph;
	while (check_end(ph, 0) == 0)
	{
		ft_usleep(phi->arg->time_die + 1);
		if (pthread_mutex_lock(&phi->arg->death) != 0)
			return (ft_putstr_fd("Error: mutex_lock", STDERR_FILENO), NULL);
		if (!check_end(ph, 0)
			&& get_time() - phi->last_meal >= (unsigned long)phi->arg->time_die)
		{
			if (ft_print_msg(phi, "has died") == 1)
				return (NULL);
			check_end(ph, 1);
			if (pthread_mutex_unlock(&phi->arg->death) != 0)
				return (ft_putstr_fd("Error: mutex_unlock", 2), NULL);
			return (NULL);
		}
		if (pthread_mutex_unlock(&phi->arg->death) != 0)
			return (ft_putstr_fd("Error: mutex_unlock", STDERR_FILENO), NULL);
	}
	return (NULL);
}

void	*loop(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	if (phi->id % 2 == 0)
		ft_usleep(phi->arg->time_eat / 10);
	if (pthread_create(&(phi)->th_check, NULL, monitor, (phi)) != 0)
		return (ft_putstr_fd("Error: pthread_create", STDERR_FILENO), NULL);
	while (check_end(phi, 0) == 0)
	{
		if (ft_activity(philo) != 0)
			return (NULL);
	}
	return (NULL);
}

static void	ft_create_thread(t_table *table)
{
	int	i;

	i = 0;
	table->param.start = get_time();
	while (i < table->param.nb_phi)
	{
		if (pthread_create(&table->phi[i].th, NULL, loop, &table->phi[i]) != 0)
			return (ft_putstr_fd("Error: pthread_create", STDERR_FILENO));
		i += 1;
	}
	i = 0;
	while (i < table->param.nb_phi)
	{
		if (pthread_join(table->phi[i].th, NULL) != 0)
			return (ft_putstr_fd("Error: pthread_join", STDERR_FILENO));
		if (pthread_join(table->phi[i].th_check, NULL) != 0)
			return (ft_putstr_fd("Error: pthread_join", STDERR_FILENO));
		i += 1;
	}
}

void	ft_thread(t_table *table)
{
	if (pthread_mutex_init(&table->param.print, NULL) != 0)
	{
		ft_putstr_fd("Error: mutex_init", STDERR_FILENO);
		return (error_mutex(&table, table->param.nb_phi - 1, 0));
	}
	if (pthread_mutex_init(&table->param.end, NULL) != 0)
	{
		ft_putstr_fd("Error: mutex init", STDERR_FILENO);
		return (error_mutex(&table, table->param.nb_phi - 1, 1));
	}
	if (pthread_mutex_init(&table->param.death, NULL) != 0)
	{
		ft_putstr_fd("Error: mutex init", STDERR_FILENO);
		return (error_mutex(&table, table->param.nb_phi - 1, 1));
	}
	ft_create_thread(table);
	destroy_mutex(table);
}
