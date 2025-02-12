/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:58:04 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/12 17:28:17 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*check_end(void *ph)
{
	t_philo	*phi;

	phi = (t_philo *)ph;
	while (phi->arg->dead != 1 && phi->arg->finish != phi->arg->nb_phi)
	{
		ft_usleep(phi->arg->time_die + 1);
		if (get_time() - phi->last_meal >= (unsigned long)phi->arg->time_die
			&& phi->eating != 1)
		{
			ft_print_msg(phi, "has died");
			phi->arg->dead = 1;
			return (NULL);
		}
	}
	return (NULL);
}

void	*loop(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	if (phi->id % 2 != 0)
		ft_usleep(phi->arg->time_eat / 10);
	while (phi->arg->finish != phi->arg->nb_phi && phi->arg->dead == 0)
	{
		if (pthread_create(&(phi)->th_check, NULL, check_end, (phi)) != 0)
			return (NULL);
		if (ft_activity(philo) == -1)
			return (NULL);
	}
	return (NULL);
}

int	ft_create_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->param.nb_phi)
	{
		if (pthread_create(&table->phi[i].th, NULL, loop, &table->phi[i]) != 0)
			return (-1);
		i += 1;
	}
	i = 0;
	while (i < table->param.nb_phi)
	{
		if (pthread_join(table->phi[i].th, NULL) != 0)
			return (-1);
		i += 1;
	}
	return (0);
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->param.nb_phi)
	{
		pthread_mutex_destroy(table->phi[i].r_fork);
		i++;
	}
	i = 0;
	while (i < table->param.nb_phi)
	{
		pthread_mutex_destroy(table->phi[i].r_fork);
		i++;
	}
	pthread_mutex_destroy(&table->param.end);
	pthread_mutex_destroy(&table->phi->l_fork);
	pthread_mutex_destroy(&table->param.print);
}

void	ft_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->param.nb_phi)
	{
		pthread_mutex_init(table->phi[i].r_fork, NULL);
		i++;
	}
	pthread_mutex_init(&table->param.print, NULL);
	pthread_mutex_init(&table->param.end, NULL);
	if (ft_create_thread(table) == -1)
		return (ft_putstr_fd("Error: pthread", STDERR_FILENO));
	destroy_mutex(table);
}
