/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:33:00 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/09 17:29:26 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_print_struc(t_struct struc)
{
	printf("nb philo : %d\n", struc.nb_philo);
	printf("time die : %d\n", struc.time_die);
	printf("time eat : %d\n", struc.time_eat);
	printf("time sleep : %d\n", struc.time_sleep);
	printf("must eat : %d\n", struc.must_eat);
}

long	ft_atol(const char *str)
{
	int		i;
	long	num;
	long	signe;

	signe = 1;
	num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] > '0' && str[i] < '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (signe == -1)
		num *= signe;
	return (num);
}

int	ft_checknbr(char *av)
{
	int	i;

	i = 0;
	while (((av[i] >= 9 && av[i] <= 13) || av[i] == 32))
		i++;
	if ((av[i] == '-' || av[i] == '+'))
	{
		if (av[i] == '-' || av[i + 1] < '0' || av[i + 1] > '9')
			return (-1);
		i++;
	}
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (-1);
		i++;
	}
	return (1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}
