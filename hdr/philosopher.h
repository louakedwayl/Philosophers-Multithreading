/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:56:13 by wlouaked          #+#    #+#             */
/*   Updated: 2025/01/11 19:50:18 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

/* -------------------------------------------------------------------------- */
/*                                   HEADERS                                  */
/* -------------------------------------------------------------------------- */

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

/* -------------------------------------------------------------------------- */
/*                                  STUCTURES                                 */
/* -------------------------------------------------------------------------- */

typedef struct s_philosopher{
	int				id;
	pthread_mutex_t	id_mutex;
	pthread_t		thread;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
	long			last_meal_time;
	pthread_mutex_t	meal_time_mutex;
	int				nbr_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_bites;
	int				satisfy;
	pthread_mutex_t	satisfy_m;
	struct timeval	start;
	struct timeval	end;
	pthread_mutex_t	*left_forks;
	pthread_mutex_t	*right_forks;
	struct s_table	*table;
}	t_philosopher;

typedef struct s_table {
	int				nbr_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_bites;
	bool			death;
	long			start;
	long			end;
	pthread_mutex_t	death_m;
	pthread_mutex_t	*forks;
	pthread_mutex_t	megaphone;
}	t_table;

/* -------------------------------------------------------------------------- */
/*                                 FUNCTIONS                                  */
/* -------------------------------------------------------------------------- */

int		ft_atoi(const char *str);
void	ft_init_atoi(int *i, int *val, int *is_neg);
int		ft_isdigit(int c);
int		set_table(t_table *table, char **argv);
int		init_table(t_table *table, int argc, char **argv);
void	*philosopher_routine_even(void *arg);
int		create_philo(t_philosopher *philo, t_table *table);
int		init_philo(t_philosopher *philo, t_table *table, int i);
int		handler_thread_join(t_philosopher *philo);
void	destroy_and_free_forks(t_table *table);
int		alloc_philo(t_philosopher **philo, t_table table);
int		handler_init_philo(t_philosopher **philo, t_table *table);
void	release_ressource(t_table *table, t_philosopher **philo);
int		check_death(t_philosopher *philo, t_table *table);
long	get_time_in_ms(void);
long	time_elapsed_for_start(long start_time);
void	*philosopher_routine_odd(void *arg);
bool	is_philosopher_dead(t_philosopher *philo);
void	*philosopher_routine_one(void *arg);
int		init_philo_one(t_philosopher *philo, t_table *table, int i);
int		take_forks_odd(t_philosopher *philo);
int		take_forks_even(t_philosopher *philo);
int		eat(t_philosopher *philo);
void	sleep_and_think(t_philosopher *philo);
void	destroy_id_mutex(t_philosopher *philo, int i);
int		init_philo_one(t_philosopher *philo, t_table *table, int i);

#endif
