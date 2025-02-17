/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:40:29 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/17 17:22:15 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_print_msg(t_philo *ph, char *str)
{
	if (check_end(ph, 0) == 1)
		return (-1);
	else
	{
		if (pthread_mutex_lock(&ph->arg->print) != 0)
			return (ft_putstr_fd("Error: mutex_lock", STDERR_FILENO), 1);
		printf("%ld philo %d %s\n", get_time() - ph->arg->start, ph->id, str);
		if (pthread_mutex_unlock(&ph->arg->print) != 0)
			return (ft_putstr_fd("Error: mutex_unlock", STDERR_FILENO), 1);
	}
	return (0);
}

static int	case_if_even(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->l_fork) != 0)
		return (ft_putstr_fd("Error: mutex_lock", STDERR_FILENO), -1);
	if (ft_print_msg(ph, "has taken a fork") == 1)
		return (-1);
	if (pthread_mutex_lock(ph->r_fork) != 0)
		return (ft_putstr_fd("Error: mutex_lock", STDERR_FILENO), -1);
	return (0);
}

static int	ft_take_fork(t_philo *ph)
{
	if (ph->id % 2 == 0)
	{
		if (case_if_even(ph) != 0)
			return (-1);
	}
	else
	{
		if (pthread_mutex_lock(ph->r_fork) != 0)
			return (ft_putstr_fd("Error: mutex_lock", STDERR_FILENO), -1);
		if (ft_print_msg(ph, "has taken a fork") == 1)
			return (-1);
		if (ph->arg->nb_phi == 1)
		{
			ft_usleep(ph->arg->time_die + 10);
			if (pthread_mutex_unlock(&ph->l_fork) != 0)
				return (ft_putstr_fd("Error: mutex_lock", STDERR_FILENO), -1);
			return (1);
		}
		if (pthread_mutex_lock(&ph->l_fork) != 0)
			return (ft_putstr_fd("Error: mutex_lock", STDERR_FILENO), -1);
	}
	return (0);
}

static int	ft_eat(t_philo *ph)
{
	if (ft_take_fork(ph) != 0)
		return (-1);
	if (ft_print_msg(ph, "has taken a fork") == 1)
		return (-1);
	if (ft_print_msg(ph, "is eating") == 1)
		return (-1);
	if (pthread_mutex_lock(&ph->arg->death) != 0)
		return (ft_putstr_fd("Error: mutex_lock", STDERR_FILENO), -1);
	ph->last_meal = (long)get_time();
	if (pthread_mutex_unlock(&ph->arg->death) != 0)
		return (ft_putstr_fd("Error: mutex_unlock", STDERR_FILENO), -1);
	ft_usleep(ph->arg->time_eat);
	ph->nb_meal += 1;
	ph->eating = 0;
	if (pthread_mutex_unlock(&ph->l_fork) != 0)
		return (ft_putstr_fd("Error: mutex_unlock", STDERR_FILENO), -1);
	if (pthread_mutex_unlock(ph->r_fork) != 0)
		return (ft_putstr_fd("Error: mutex_unlock", STDERR_FILENO), -1);
	return (0);
}

int	ft_activity(t_philo *ph)
{
	if (check_end(ph, 0) == 0)
	{
		if (ft_eat(ph) != 0)
			return (1);
	}
	if (pthread_mutex_lock(&ph->arg->end) != 0)
		return (ft_putstr_fd("Error: mutex_lock", STDERR_FILENO), 1);
	if (ph->nb_meal == ph->arg->must_eat)
		ph->arg->finish += 1;
	if (pthread_mutex_unlock(&ph->arg->end) != 0)
		return (ft_putstr_fd("Error: mutex_unlock", STDERR_FILENO), 1);
	if (check_end(ph, 0) == 1)
		return (0);
	if (ft_print_msg(ph, "is sleeping") != 0)
		return (-1);
	ft_usleep(ph->arg->time_sleep);
	if (ft_print_msg(ph, "is thinking") != 0)
		return (-1);
	return (0);
}
