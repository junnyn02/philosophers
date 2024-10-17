/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:06:37 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/17 15:31:57 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_param
{
	int				nb_phi;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				must_eat;
	pthread_mutex_t	print;
}	t_param;

typedef struct s_philo
{
	int				id;
	int				finish;
	int				death;
	size_t			start_time;
	pthread_t		th;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	t_param			*arg;
}	t_philo;

typedef struct s_table
{
	t_param			param;
	t_philo			*phi;
}	t_table;

void	ft_init_lst(t_table *param);

void	ft_putstr_fd(char *str, int fd);
void	ft_print_struc(t_table param);
void	ft_thread(t_table *param);

int		ft_checknbr(char *av);

long	ft_atol(const char *str);


#endif