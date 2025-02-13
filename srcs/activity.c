/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:40:29 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/13 17:46:28 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_print_msg(t_philo *ph, char *str)
{
	if (check_end(ph) == 1)
		return (-1);
	else
	{
		if (pthread_mutex_lock(&ph->arg->print) != 0)
			return (-1);
		printf("%ld philo %d %s\n", get_time() - ph->arg->start, ph->id, str);
		if (pthread_mutex_unlock(&ph->arg->print) != 0)
			return (-1);
	}
	return (0);
}

int	ft_eat(t_philo *ph)
{
	if (ph->arg->nb_phi == 1)
	{
		if (pthread_mutex_lock(&ph->l_fork) != 0)
			return (-1);
		if (ft_print_msg(ph, "has taken a fork") == -1)
			return (-1);
		ft_usleep(ph->arg->time_die + 10);
		if (pthread_mutex_unlock(&ph->l_fork) != 0)
			return (-1);
		return (-1);
	}
	if (ph->id % 2 == 0)
	{
		if (pthread_mutex_lock(&ph->l_fork) != 0)
			return (-1);
		if (ft_print_msg(ph, "has taken a fork") == -1)
			return (-1);
		if (pthread_mutex_lock(ph->r_fork) != 0)
			return (-1);
	}
	else
	{
		if (pthread_mutex_lock(ph->r_fork) != 0)
			return (-1);
		if (ft_print_msg(ph, "has taken a fork") == -1)
			return (-1);
		if (pthread_mutex_lock(&ph->l_fork) != 0)
			return (-1);
	}
	if (ft_print_msg(ph, "has taken a fork") == -1)
		return (-1);
	if (ft_print_msg(ph, "is eating") == -1)
		return (-1);
	if (pthread_mutex_lock(&ph->arg->death) != 0)
		return (-1);
	ph->last_meal = (long)get_time();
	if (pthread_mutex_unlock(&ph->arg->death) != 0)
		return (-1);
	ft_usleep(ph->arg->time_eat);
	ph->nb_meal += 1;
	ph->eating = 0;
	if (pthread_mutex_unlock(&ph->l_fork) != 0)
		return (-1);
	if (pthread_mutex_unlock(ph->r_fork) != 0)
		return (-1);
	return (0);
}

int	ft_sleep(t_philo *ph)
{
	if (ft_print_msg(ph, "is sleeping") == -1)
		return (-1);
	ft_usleep(ph->arg->time_sleep);
	return (0);
}

int	ft_think(t_philo *ph)
{
	if (ft_print_msg(ph, "is thinking") == -1)
		return (-1);
	return (0);
}

int	ft_activity(t_philo *ph)
{
	if (check_end(ph) == 0)
	{
		if (ft_eat(ph) == -1)
			return (-1);
	}
	pthread_mutex_lock(&ph->arg->end);
	if (ph->nb_meal == ph->arg->must_eat)
		ph->arg->finish += 1;
	pthread_mutex_unlock(&ph->arg->end);
	if (check_end(ph) == 1)
		return (0);
	if (check_end(ph) == 0)
		ft_sleep(ph);
	if (check_end(ph) == 0)
		ft_think(ph);
	return (0);
}
