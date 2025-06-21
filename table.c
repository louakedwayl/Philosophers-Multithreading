/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:14:42 by wlouaked          #+#    #+#             */
/*   Updated: 2025/01/11 17:03:44 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/philosopher.h"

int	set_table(t_table *table, char **argv)
{
	table->nbr_philosophers = ft_atoi(argv[1]);
	if (table->nbr_philosophers <= 0 || table->nbr_philosophers > 200)
	{
		printf("Error: The number of philosophers must be between 1 and 200\n");
		return (EXIT_FAILURE);
	}
	table->time_to_die = ft_atoi(argv[2]);
	if (table->time_to_die <= 0)
	{
		printf("Error: The time to die must be greater than 0\n");
		return (EXIT_FAILURE);
	}
	table->time_to_eat = ft_atoi(argv[3]);
	if (table->time_to_eat <= 0)
	{
		printf("Error: The time to die must be greater than 0\n");
		return (EXIT_FAILURE);
	}
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->time_to_sleep <= 0)
	{
		printf("Error: The time to die must be greater than 0\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_forks(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	table->forks = malloc (sizeof(pthread_mutex_t) * table->nbr_philosophers);
	if (!table->forks)
	{
		exit (EXIT_FAILURE);
	}
	while (i < table->nbr_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (j < i)
			{
				pthread_mutex_destroy(&table->forks[j]);
				j++;
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_table(t_table *table, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: The program requires between 5 and 6 arguments.\n");
		return (EXIT_FAILURE);
	}
	if (set_table(table, argv))
		return (EXIT_FAILURE);
	if (argv[5])
	{
		table->nbr_of_bites = ft_atoi(argv[5]);
		if (table->nbr_of_bites <= 0)
		{
			printf("Error: The number of bites must be greater than 0\n");
			return (EXIT_FAILURE);
		}
	}
	else
		table->nbr_of_bites = -2;
	init_forks(table);
	pthread_mutex_init(&(table->megaphone), NULL);
	pthread_mutex_init(&(table->death_m), NULL);
	table->start = get_time_in_ms();
	table->death = false;
	return (EXIT_SUCCESS);
}

void	destroy_and_free_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free (table->forks);
}
