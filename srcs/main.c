/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:07:25 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/17 16:57:49 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_fill_arg(t_table **arg, long nbr, int i)
{
	if (i == 1)
		(*arg)->param.nb_phi = nbr;
	else if (i == 2)
		(*arg)->param.time_die = nbr;
	else if (i == 3)
		(*arg)->param.time_eat = nbr;
	else if (i == 4)
		(*arg)->param.time_sleep = nbr;
	else if (i == 5)
		(*arg)->param.must_eat = nbr;
}

int	ft_parse(char **av, t_table *arg)
{
	int		i;
	long	nbr;

	i = 1;
	arg->param.start = 0;
	arg->param.must_eat = -1;
	arg->param.dead = 0;
	arg->param.finish = 0;
	while (av[i])
	{
		if (ft_checknbr(av[i]) == -1)
			return (ft_putstr_fd("Error: invalid arg\n", STDERR_FILENO), -1);
		nbr = ft_atol(av[i]);
		if (nbr > INT_MAX || nbr <= 0)
			return (ft_putstr_fd("Error: invalid arg\n", STDERR_FILENO), -1);
		ft_fill_arg(&arg, nbr, i);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	table.phi = NULL;
	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Error: numbers of args\n", STDERR_FILENO), 1);
	if (ft_parse(av, &table) == -1)
		return (2);
	ft_init_lst(&table);
	if (!table.phi)
		return (3);
	ft_thread(&table);
	return (0);
}
