/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:06:37 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/24 16:52:58 by junguyen         ###   ########.fr       */
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
	int				dead;
	long			start;
	pthread_mutex_t	print;
}	t_param;

typedef struct s_philo
{
	int				id;
	int				finish;
	int				eating;
	long			last_meal;
	pthread_t		th;
	pthread_t		th_check;
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
void	ft_print_struc(t_table param); // a supp
void	ft_thread(t_table *param);
void	ft_usleep(size_t time);

int		ft_checknbr(char *av);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);
int		ft_activity(t_philo *ph);

long	ft_atol(const char *str);

size_t	get_time(void);

#endif