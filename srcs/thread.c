/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:58:04 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/13 17:58:04 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_end(t_philo *ph)
{
	pthread_mutex_lock(&ph->arg->end);
	if (ph->arg->dead == 1 || ph->arg->finish == ph->arg->nb_phi)
	{
		pthread_mutex_unlock(&ph->arg->end);
		return (1);
	}
	pthread_mutex_unlock(&ph->arg->end);
	return (0);
}

void	*monitor(void *ph)
{
	t_philo	*phi;

	phi = (t_philo *)ph;
	while (check_end(ph) == 0)
	{
		ft_usleep(phi->arg->time_die + 1);
		pthread_mutex_lock(&phi->arg->death);
		if (get_time() - phi->last_meal >= (unsigned long)phi->arg->time_die)
		{
			if (phi->arg->dead == 1)
			{
				pthread_mutex_unlock(&phi->arg->death);
				return (NULL);
			}
			ft_print_msg(phi, "has died");
			phi->arg->dead = 1;
			pthread_mutex_unlock(&phi->arg->death);
			return (NULL);
		}
		pthread_mutex_unlock(&phi->arg->death);
	}
	return (NULL);
}

void	*loop(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	if (phi->id % 2 != 0 && phi->arg->nb_phi != 1)
		ft_usleep(phi->arg->time_eat / 10);
	while (check_end(phi) == 0)
	{
		if (pthread_create(&(phi)->th_check, NULL, monitor, (phi)) != 0)
			return (NULL);
		if (ft_activity(philo) == -1)
			return (NULL);
		if (pthread_join(phi->th_check, NULL) != 0)
			return (NULL);
		// pthread_detach(phi->th_check);
	}
	return (NULL);
}

int	ft_create_thread(t_table *table)
{
	int	i;

	i = 0;
	if (table->param.start == 0)
		table->param.start = get_time();
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
		// if (pthread_join(table->phi[i].th_check, NULL) != 0)
		// 	return (-1);
		// pthread_detach(table->phi[i].th_check);
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
		pthread_mutex_destroy(&table->phi[i].l_fork);
		i++;
	}
	i = 0;
	// while (i < table->param.nb_phi)
	// {
	// 	pthread_mutex_destroy(table->phi[i].r_fork);
	// 	i++;
	// }
	pthread_mutex_destroy(&table->param.end);
	// pthread_mutex_destroy(&table->phi->l_fork);
	pthread_mutex_destroy(&table->param.print);
	pthread_mutex_destroy(&table->param.death);
}

void	ft_thread(t_table *table)
{
	int	i;

	i = 0;
	// while (i < table->param.nb_phi)
	// {
	// 	pthread_mutex_init(&table->phi[i].l_fork, NULL);
	// 	// pthread_mutex_init(table->phi[i].r_fork, NULL);
	// 	i++;
	// }
	pthread_mutex_init(&table->param.print, NULL);
	pthread_mutex_init(&table->param.end, NULL);
	pthread_mutex_init(&table->param.death, NULL);
	if (ft_create_thread(table) == -1)
		return (ft_putstr_fd("Error: pthread", STDERR_FILENO));
	destroy_mutex(table);
}
