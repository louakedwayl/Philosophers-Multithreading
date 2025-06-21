/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:21:07 by wlouaked          #+#    #+#             */
/*   Updated: 2025/01/11 19:47:29 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/philosopher.h"

int	take_forks_odd(t_philosopher *philo)
{
	if (is_philosopher_dead(philo))
		return (EXIT_FAILURE);
	pthread_mutex_lock(philo->right_forks);
	pthread_mutex_lock(&(philo->table->megaphone));
	printf ("%ld ", time_elapsed_for_start(philo->table->start));
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&(philo->table->megaphone));
	if (is_philosopher_dead(philo))
	{
		pthread_mutex_unlock((philo->right_forks));
		return (EXIT_FAILURE);
	}
	pthread_mutex_lock((philo->left_forks));
	pthread_mutex_lock(&(philo->table->megaphone));
	printf ("%ld ", time_elapsed_for_start(philo->table->start));
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&(philo->table->megaphone));
	return (EXIT_SUCCESS);
}

int	take_forks_even(t_philosopher *philo)
{
	if (is_philosopher_dead(philo))
		return (EXIT_FAILURE);
	pthread_mutex_lock((philo->left_forks));
	pthread_mutex_lock(&(philo->table->megaphone));
	printf ("%ld ", time_elapsed_for_start(philo->table->start));
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&(philo->table->megaphone));
	if (is_philosopher_dead(philo))
	{
		pthread_mutex_unlock((philo->left_forks));
		return (EXIT_FAILURE);
	}
	pthread_mutex_lock((philo->right_forks));
	pthread_mutex_lock(&(philo->table->megaphone));
	printf ("%ld ", time_elapsed_for_start(philo->table->start));
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&(philo->table->megaphone));
	return (EXIT_SUCCESS);
}

int	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&(philo->meal_time_mutex));
	philo->last_meal_time = time_elapsed_for_start(philo->table->start);
	philo->last_meal_time += philo->time_to_eat;
	pthread_mutex_unlock(&(philo->meal_time_mutex));
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&(philo->meal_mutex));
	pthread_mutex_lock(&(philo->id_mutex));
	pthread_mutex_lock(&(philo->table->megaphone));
	printf ("%ld ", time_elapsed_for_start(philo->table->start));
	printf("%d is eating\n", philo->id);
	pthread_mutex_unlock(&(philo->id_mutex));
	pthread_mutex_unlock(&(philo->table->megaphone));
	usleep (philo->time_to_eat * 1000);
	pthread_mutex_unlock((philo->left_forks));
	pthread_mutex_unlock((philo->right_forks));
	return (EXIT_SUCCESS);
}

void	sleep_and_think(t_philosopher *philo)
{
	pthread_mutex_lock(&(philo->id_mutex));
	pthread_mutex_lock(&(philo->table->megaphone));
	printf ("%ld ", time_elapsed_for_start(philo->table->start));
	printf("%d is sleeping\n", philo->id);
	pthread_mutex_unlock(&(philo->id_mutex));
	pthread_mutex_unlock(&(philo->table->megaphone));
	usleep (philo->time_to_sleep * 1000);
	pthread_mutex_lock(&(philo->id_mutex));
	pthread_mutex_lock(&(philo->table->megaphone));
	printf ("%ld ", time_elapsed_for_start(philo->table->start));
	printf("%d is thinking\n", philo->id);
	pthread_mutex_unlock(&(philo->id_mutex));
	pthread_mutex_unlock(&(philo->table->megaphone));
}
