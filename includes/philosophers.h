/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:06:37 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/09 17:26:36 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_struct
{
	int	nb_philo;
	int	time_eat;
	int	time_sleep;
	int	time_die;
	int	must_eat;
}	t_struct;

void	ft_putstr_fd(char *str, int fd);
void	ft_print_struc(t_struct struc);

int		ft_checknbr(char *av);

long	ft_atol(const char *str);

#endif