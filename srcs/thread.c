/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:58:04 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/17 16:34:22 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*loop(void *philo)
{
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	if (((t_philo *)philo)->start_time == 0)
		((t_philo *)philo)->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	// printf("start_time : %zu\n", ((t_philo *)philo)->start_time);
	if (((t_philo *)philo)->id % 2 == 0 && ((t_philo *)philo)->finish == 0)
		usleep(((t_philo *)philo)->arg->time_eat);
	if (pthread_mutex_lock(((t_philo *)philo)->r_fork) != 0)
		return ((int *)-1);
	if (pthread_mutex_lock(&((t_philo *)philo)->l_fork) != 0)
		return ((int *)-1);
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	// printf("time die : %zu\n", (unsigned long)((t_philo *)philo)->arg->time_die);
	// printf("eta : %zu\n", time);
	if (time - ((t_philo *)philo)->start_time > (unsigned long)((t_philo *)philo)->arg->time_die)
	{
		if (pthread_mutex_lock(&((t_philo *)philo)->arg->print) != 0)
			return ((int *)-1);
		gettimeofday(&tv, NULL);
		time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		printf("%ld %d has died\n", time, ((t_philo *)philo)->id);
		if (pthread_mutex_unlock(&((t_philo *)philo)->arg->print) != 0)
			return ((int *)-1);
		if (pthread_mutex_unlock(((t_philo *)philo)->r_fork) != 0)
			return ((int *)-1);
		if (pthread_mutex_unlock(&((t_philo *)philo)->l_fork) != 0)
			return ((int *)-1);
		((t_philo *)philo)->death += 1;
		return ((int *)-1);
	}
	if (pthread_mutex_lock(&((t_philo *)philo)->arg->print) != 0)
		return ((int *)-1);
	// if (tv.tv_usec - start < (unsigned long)((t_philo *)philo)->arg->time_die)
	// {
	// 	if (pthread_mutex_unlock(((t_philo *)philo)->r_fork) != 0)
	// 		return ((int *)-1);
	// 	if (pthread_mutex_unlock(&((t_philo *)philo)->l_fork) != 0)
	// 		return ((int *)-1);
	// 	((t_philo *)philo)->finish += 1;
	// 	if (pthread_mutex_lock(&((t_philo *)philo)->arg->print) != 0)
	// 		return ((int *)-1);
	// 	printf("%ld %d is dead\n", tv.tv_usec, ((t_philo *)philo)->id);
	// 	if (pthread_mutex_unlock(&((t_philo *)philo)->arg->print) != 0)
	// 		return ((int *)-1);
	// }
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("%ld %d has taken a fork\n", time, ((t_philo *)philo)->id);
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("%ld %d is eating\n", time, ((t_philo *)philo)->id);
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
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("%ld %d is sleeping\n", time, ((t_philo *)philo)->id);
	if (pthread_mutex_unlock(&((t_philo *)philo)->arg->print) != 0)
		return ((int *)-1);
	usleep(((t_philo *)philo)->arg->time_sleep * 1000);
	if (pthread_mutex_lock(&((t_philo *)philo)->arg->print) != 0)
		return ((int *)-1);
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("%ld %d is thinking\n", time, ((t_philo *)philo)->id);
	if (pthread_mutex_unlock(&((t_philo *)philo)->arg->print) != 0)
		return ((int *)-1);
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	((t_philo *)philo)->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	// printf("start time : %zu\n", ((t_philo *)philo)->start_time);
	return ((int *)0);
}

void	ft_create_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->param.nb_phi)
	{
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
		if (table->phi[i].death == 1)
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
			ft_create_thread(table);
		if (check_finish_meal(table) == 1)
			printf("All philosophers ate %d time.s\n", table->param.must_eat);
	}
	else
	{
		while (check_death(table) == 0)
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
	pthread_mutex_destroy(&table->param.print);
}
