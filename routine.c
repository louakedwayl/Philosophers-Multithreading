/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:08:00 by wlouaked          #+#    #+#             */
/*   Updated: 2025/01/11 20:10:09 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/philosopher.h"

int	ft_ets(t_philosopher	*philo)
{
	eat(philo);
	if (is_philosopher_dead(philo))
		return (EXIT_FAILURE);
	sleep_and_think(philo);
	if (is_philosopher_dead(philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	unlock_both(t_philosopher	*philo)
{
	pthread_mutex_unlock((philo->right_forks));
	pthread_mutex_unlock((philo->left_forks));
}

void	*philosopher_routine_odd(void *arg)
{
	t_philosopher	*philo;
	int				i;

	philo = (t_philosopher *)arg;
	i = 1;
	while (1)
	{
		if (is_philosopher_dead(philo))
			return (NULL);
		if (take_forks_odd(philo))
			return (NULL);
		if (is_philosopher_dead(philo))
			return (unlock_both(philo), (NULL));
		if (ft_ets(philo))
			return (NULL);
		if (i++ >= philo->nbr_of_bites)
		{
			pthread_mutex_lock((&philo->satisfy_m));
			philo->satisfy = 1;
			pthread_mutex_unlock((&philo->satisfy_m));
		}
	}
	return (NULL);
}

void	*philosopher_routine_even(void *arg)
{
	t_philosopher	*philo;
	int				i;

	i = 1;
	philo = (t_philosopher *)arg;
	usleep ((philo->time_to_eat * 1000));
	while (1)
	{
		if (is_philosopher_dead(philo))
			return (NULL);
		if (take_forks_even(philo))
			return (NULL);
		if (is_philosopher_dead(philo))
			return (unlock_both(philo), (NULL));
		if (ft_ets(philo))
			return (NULL);
		if (i++ >= philo->nbr_of_bites)
		{
			pthread_mutex_lock((&philo->satisfy_m));
			philo->satisfy = 1;
			pthread_mutex_unlock((&philo->satisfy_m));
		}
	}
	return (NULL);
}

void	*philosopher_routine_one(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	printf ("%ld ", time_elapsed_for_start(philo->table->start));
	printf("%d has taken a fork\n", philo->id);
	usleep ((philo->time_to_die * 1000));
	printf ("%d %d died\n", philo->time_to_die, philo->id);
	return (NULL);
}
