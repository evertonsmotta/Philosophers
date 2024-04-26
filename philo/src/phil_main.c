/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:21:35 by evdos-sa          #+#    #+#             */
/*   Updated: 2023/09/18 18:24:36 by evdos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ph_error(void)
{
	printf("Invalid argument!\n");
	printf("Follow one of the examples below:\n");
	printf("./philo 4 800 200 200 5\n");
	printf("./philo 4 800 200 200\n");
	printf("Rules:\n");
	printf("av[0] = program name: ./philo\n");
	printf("av[1] = nb_philos: 1-200\n");
	printf("av[2] = time_to_die: 60+\n");
	printf("av[3] = time_to_eat: 60+\n");
	printf("av[4] = time_to_sleep: 60+\n");
	printf("av[5] = number_of_times_each_philosopher_must_eat: ");
	printf("0+\n");
	exit (1);
}

int	ft_atoi(char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] && str[i] <= 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res * sign);
}

int	ph_is_digit(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (++i < ac)
		while (av[i][++j])
			if (av[i][j] < '0' && av[i][j] > '9')
				return (1);
	return (0);
}

int	main(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		ph_error();
	else if (ph_is_digit(ac, av))
		ph_error();
	else if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		ph_error();
	else if (ac == 6 && ft_atoi(av[5]) <= 0)
		ph_error();
	else
		while (++i < 5)
			if (ft_atoi(av[i]) < 60)
				ph_error();
	if (philosophers(ac, av) != 0)
		return (EXIT_FAILURE);
	return (0);
}
