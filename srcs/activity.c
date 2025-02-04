/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:40:29 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/24 18:30:26 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_eat(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->l_fork) != 0)
		return (-1);
	if(ph->arg->start == 0)
		ph->arg->start= get_time();
	if (pthread_mutex_lock(&ph->arg->print) != 0)
		return (-1);
	printf("%ld philo %d has taken a fork\n", (long)get_time() - ph->arg->start, ph->id);
	if (pthread_mutex_unlock(&ph->arg->print) != 0)
		return (-1);
	if (pthread_mutex_lock(ph->r_fork) != 0)
		return (-1);
	if (pthread_mutex_lock(&ph->arg->print) != 0)
		return (-1);
	printf("%ld philo %d has taken a fork\n", (long)get_time() - ph->arg->start, ph->id);
	printf("%ld philo %d is eating\n", (long)get_time() - ph->arg->start, ph->id);
	if (pthread_mutex_unlock(&ph->arg->print) != 0)
		return (-1);
	ph->eating = 1;
	ft_usleep(ph->arg->time_eat);
	ph->finish += 1;
	ph->eating = 0;
	ph->last_meal = (long)get_time();
	if (pthread_mutex_unlock(ph->r_fork) != 0)
		return (-1);
	if (pthread_mutex_unlock(&ph->l_fork) != 0)
		return (-1);
	return (0);
}

int	ft_sleep(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->arg->print) != 0)
		return (-1);
	printf("%ld philo %d is sleeping\n", (long)get_time() - ph->arg->start, ph->id);
	if (pthread_mutex_unlock(&ph->arg->print) != 0)
		return (-1);
	ft_usleep(ph->arg->time_sleep);
	return (0);
}

int	ft_think(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->arg->print) != 0)
		return (-1);
	printf("%ld philo %d is thinking\n", (long)get_time() - ph->arg->start, ph->id);
	if (pthread_mutex_unlock(&ph->arg->print) != 0)
		return (-1);
	return (0);
}

int	ft_activity(t_philo *ph)
{
	if (ph->arg->dead != 1)
		ft_eat(ph);
	if (ph->arg->dead != 1)
		ft_sleep(ph);
	if (ph->arg->dead != 1)
		ft_think(ph);
	return (0);
}
