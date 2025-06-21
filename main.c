/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:07:07 by wlouaked          #+#    #+#             */
/*   Updated: 2025/01/13 16:49:15 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/philosopher.h"

//valgrind --tool=helgrind
//./philo 1 800 200 200         
//The philosopher should not eat and should die.
//./philo 5 800 200 200			
//No philosopher should die.
// ./philo 5 800 200 200 7		
//No philosopher should die and the simulation should 
//stop when every philosopher has eaten at least 7 times.
// ./philo 4 410 200 200		
//No philosopher should die.
// ./philo 4 310 200 100		
//One philosopher should die.

int	handler_one_philo(t_table *table, t_philosopher **philo)
{
	*philo = malloc (sizeof(t_philosopher));
	if (!(*philo))
		return (EXIT_FAILURE);
	init_philo_one(*philo, table, 0);
	pthread_create(&(*philo)->thread, NULL, philosopher_routine_one,
		(void *)*philo);
	handler_thread_join(*philo);
	destroy_and_free_forks(table);
	free(*philo);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_table			table;
	t_philosopher	*philo;

	if (init_table (&table, argc, argv))
		return (EXIT_FAILURE);
	if (table.nbr_philosophers == 1)
	{
		handler_one_philo(&table, &philo);
		return (EXIT_SUCCESS);
	}
	if (handler_init_philo(&philo, &table))
		return (EXIT_FAILURE);
	check_death(philo, &table);
	handler_thread_join(philo);
	release_ressource(&table, &philo);
	return (EXIT_SUCCESS);
}
