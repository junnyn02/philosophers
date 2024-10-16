/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:58:04 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/16 18:14:56 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*loop(void *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (((t_philo *)philo)->id % 2 == 0)
		usleep(((t_philo *)philo)->arg->time_eat);
	if (pthread_mutex_lock(&((t_philo *)philo)->arg->print) != 0)
		return ((int *)-1);
	if (pthread_mutex_lock(((t_philo *)philo)->r_fork) != 0)
		return ((int *)-1);
	if (pthread_mutex_lock(&((t_philo *)philo)->l_fork) != 0)
		return ((int *)-1);
	printf("%ld %d has taken a fork\n", tv.tv_usec, ((t_philo *)philo)->id);
	printf("%ld %d is eating\n", tv.tv_usec, ((t_philo *)philo)->id);
	if (pthread_mutex_unlock(&((t_philo *)philo)->arg->print) != 0)
		return ((int *)-1);
	usleep(((t_philo *)philo)->arg->time_eat * 1000);
	if (pthread_mutex_unlock(((t_philo *)philo)->r_fork) != 0)
		return ((int *)-1);
	if (pthread_mutex_unlock(&((t_philo *)philo)->l_fork) != 0)
		return ((int *)-1);
	((t_philo *)philo)->finish += 1;
	if (pthread_mutex_lock(&((t_philo *)philo)->arg->print) != 0)
		return ((int *)-1);
	printf("%ld %d is sleeping\n", tv.tv_usec, ((t_philo *)philo)->id);
	if (pthread_mutex_unlock(&((t_philo *)philo)->arg->print) != 0)
		return ((int *)-1);
	usleep(((t_philo *)philo)->arg->time_sleep * 1000);
	if (pthread_mutex_lock(&((t_philo *)philo)->arg->print) != 0)
		return ((int *)-1);
	printf("%ld %d is thinking\n", tv.tv_usec, ((t_philo *)philo)->id);
	if (pthread_mutex_unlock(&((t_philo *)philo)->arg->print) != 0)
		return ((int *)-1);
	return ((int *)0);
}

void	ft_create_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->param.nb_phi)
	{
		table->phi[i].arg = &table->param;
		if (pthread_create(&table->phi[i].th, NULL, loop, &table->phi[i]) != 0)
			return ;
		i += 1;
	}
	i = 0;
	while (i < table->param.nb_phi)
	{
		if (pthread_join(table->phi[i].th, NULL) != 0)
			return ;
		i += 1;
	}
}

int	check_finish_meal(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->param.nb_phi)
	{
		if (table->phi[i].finish != table->param.must_eat)
			return (0);
		i++;
	}
	return (1);
}

int	check_death(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->param.nb_phi)
	{
		if (table->phi[i].finish == 1)
			return (1);
		i++;
	}
	return (0);
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
	pthread_mutex_init(&table->phi->l_fork, NULL);
	pthread_mutex_init(&table->param.print, NULL);
	if (table->param.must_eat != 0)
	{
		while (check_finish_meal(table) == 0 && check_death(table) == 0)
		{
			ft_create_thread(table);
		}
		printf("All philosophers ate %d time.s\n", table->param.must_eat);
	}
	else
	{
		ft_create_thread(table);
		ft_create_thread(table);
	}
	i = 0;
	while (i < table->param.nb_phi)
	{
		pthread_mutex_destroy(table->phi[i].r_fork);
		i++;
	}
	pthread_mutex_destroy(table->phi->r_fork);
	pthread_mutex_destroy(&table->phi->l_fork);
	pthread_mutex_init(&table->param.print, NULL);
}
