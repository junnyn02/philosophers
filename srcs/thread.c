/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:58:04 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/25 17:49:48 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*check_end(void *ph)
{
	while (((t_philo *)ph)->arg->dead != 1 && ((t_philo *)ph)->finish != ((t_philo *)ph)->arg->must_eat)
	{
		ft_usleep(((t_philo *)ph)->arg->time_die + 1);
		if (((t_philo *)ph)->finish == ((t_philo *)ph)->arg->must_eat)
			return ((int *)1);
		if (get_time() - ((t_philo *)ph)->last_meal >= (unsigned long)((t_philo *)ph)->arg->time_die && ((t_philo *)ph)->eating != 1)
		{
			if (pthread_mutex_lock(&((t_philo *)ph)->arg->print) != 0)
				return ((int *)-1);
			printf("%ld philo %d has died\n", (long)get_time() - ((t_philo *)ph)->arg->start, ((t_philo *)ph)->id);
			if (pthread_mutex_unlock(&((t_philo *)ph)->arg->print) != 0)
				return ((int *)-1);
			((t_philo *)ph)->arg->dead = 1;
			return ((int *)-1);
		}
	}
	return ((int *)0);
}

void	*loop(void *philo)
{
	if (pthread_create(&((t_philo *)philo)->th_check, NULL,
			check_end, ((t_philo *)philo)) != 0)
		return ((int *)-1);
	if (((t_philo *)philo)->id % 2 != 0)
		ft_usleep(((t_philo *)philo)->arg->time_eat / 10);
	while (((t_philo *)philo)->arg->dead != 1 && ((t_philo *)philo)->finish != ((t_philo *)philo)->arg->must_eat)
		ft_activity(philo);
	// pthread_detach(((t_philo *)philo)->th_check);
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

// int	check_death(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	while (i < table->param.nb_phi)
// 	{
// 		if (table->phi[i].death == 1)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

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
	if (table->param.must_eat != 0)
	{
		while (check_finish_meal(table) == 0 && table->param.dead == 0)
			ft_create_thread(table);
		if (check_finish_meal(table) == 1)
			printf("All philosophers ate %d time.s\n", table->param.must_eat);
	}
	else
	{
		while (table->param.dead == 0)
			ft_create_thread(table);
	}
	// ft_create_thread(table);
	// if (check_finish_meal(table) == 1)
	// 	printf("All philosophers ate %d time.s\n", table->param.must_eat);
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
