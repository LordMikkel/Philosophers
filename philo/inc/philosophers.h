/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:06:59 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/24 22:43:16 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ************************************************************************** */
/*                               Includes                                     */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

/* ************************************************************************** */
/*                               Structure                                    */
/* ************************************************************************** */

typedef struct s_dinner		t_dinner;
typedef struct s_monitor	t_monitor;
typedef struct s_philo		t_philo;

struct s_philo
{
	int				id;
	int				meals;
	unsigned int	starvation;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	t_dinner		*dinner;

};

struct s_monitor
{
	int				*forks_available;
	pthread_mutex_t	service_mutex;
	pthread_t		thread;
	t_dinner		*dinner;
};

struct s_dinner
{
	int				total;
	int				dead;
	int				eat;
	int				sleep;
	int				meals;
	int				stop;
	unsigned int	start;
	pthread_mutex_t	print_mutex;
	t_monitor		monitor;
	t_philo			*philosophers;
};

/* ************************************************************************** */
/*                              philosophers                                  */
/* ************************************************************************** */
void			wait_for_threads(t_dinner *dinner);
/* ************************************************************************** */
/*                             Initialization                                 */
/* ************************************************************************** */
int				is_valid_args(int ac, char **av);
int				init_dinner(t_dinner *dinner, int ac, char **av);
int				allocate_philosophers(t_dinner *dinner);
int				init_philosopher(t_philo *philo, int id, t_dinner *dinner);
int				init_monitor(t_monitor *monitor, t_dinner *dinner);
void			init_forks(t_monitor *monitor);

/* ************************************************************************** */
/*                                 time                                       */
/* ************************************************************************** */
unsigned int	get_current_time(void);

/* ************************************************************************** */
/*                                 clean                                      */
/* ************************************************************************** */
void			clean_dinner(t_dinner *dinner);
void			clean_philosophers(t_dinner *dinner);
void			clean_monitor(t_monitor *monitor);

/* ************************************************************************** */
/*                                 exit                                       */
/* ************************************************************************** */
void			error(char *error, t_dinner *dinner);

/* ************************************************************************** */
/*                                 utils                                      */
/* ************************************************************************** */
void			put_str_fd(int fd, char *s);
int				ft_atoi(const char *nptr);
bool			ft_atoi_range(const char *nptr);
int				ft_isdigit(int c);

/* ************************************************************************** */
/*                                Limits                                      */
/* ************************************************************************** */
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define TRUE 1
# define FALSE 0
# define FAIL 0
# define SUCCES 1
# define FREE 1
# define TAKEN 0
# define NO_ATRIBUTE 0
# define NO_RETURN_VALUE 0

/* ************************************************************************** */
/*                                Messages                                    */
/* ************************************************************************** */
# define DIED "%s died\n"
# define EATING "%s is eating\n"
# define THINKING "%s is thinking\n"
# define SLEEPING "%s is sleeping\n"
# define TAKE_FORKS "%s has taken a fork\n"
# define ERR_ARGS "Usage: ./philo philos die(ms) eat(ms) sleep(ms) [meals]\n"
# define ERR_INT "Error: Arguments must be positive integers (1-2147483647)\n"
# define ERR_MEM "Error: Memory alloc failed. Check system resources\n"
# define ERR_MUTEX_INIT "Error: Failed to initialize print mutex\n"
# define ERR_MUTEX_DESTROY "Error: Failed to destroy mutex\n"
# define ERR_TIME "Error: Failed to get system time\n"

#endif
