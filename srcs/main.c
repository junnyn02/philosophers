/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:07:25 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/09 17:33:08 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_parse(char **av, t_struct *struc)
{
	int		i;
	long	nbr;

	i = 1;
	struc->must_eat = 0;
	while (av[i])
	{
		if (ft_checknbr(av[i]) == -1)
			return (ft_putstr_fd("Error: not a valid int\n", STDERR_FILENO), -1);
		nbr = ft_atol(av[i]);
		if (nbr > INT_MAX)
			return (ft_putstr_fd("Error: not a valid int\n", STDERR_FILENO), -1);
		if (i == 1)
			struc->nb_philo = (int)nbr;
		else if (i == 2)
			struc->time_die = (int)nbr;
		else if (i == 3)
			struc->time_eat = (int)nbr;
		else if (i == 4)
			struc->time_sleep = (int)nbr;
		else if (i == 5)
			struc->must_eat = (int)nbr;
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_struct	struc;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Error: numbers of args\n", STDERR_FILENO), -1);
	if (ft_parse(av, &struc) == -1)
		return (-2);
	ft_print_struc(struc);
	return (0);
}
