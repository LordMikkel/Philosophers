/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:06:59 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/04 17:49:59 by migarrid         ###   ########.fr       */
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
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>

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
	pid_t			pid;
	t_monitor		*monitor;
	t_dinner		*dinner;
};

struct s_monitor
{
	sem_t			*forks;
	sem_t			*print;
	sem_t			*meals;
	sem_t			*death;
	sem_t			*end;
	pthread_t		*threads;
	t_philo			*philosophers;
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
	t_monitor		monitor;
	t_philo			*philosophers;
};

/* ************************************************************************** */
/*                              philosophers                                  */
/* ************************************************************************** */
int				start_simulation(t_dinner *dinner);
int				philosopher_routine(t_philo *philosopher);
void			*monitor_routine(void *arg);
void			one_philosopher(t_philo *philosopher);
int				wait_for_simulation(t_dinner *dinner);
int				safe_read_end(t_dinner *dinner);
void			end_simulation(t_dinner *dinner);

/* ************************************************************************** */
/*                                 Actions                                    */
/* ************************************************************************** */
void			thinks(t_philo *philosopher);
void			eats(t_philo *philosopher);
void			sleeps(t_philo *philosopher);
void			death(t_philo *philo);

/* ************************************************************************** */
/*                            status and Service                              */
/* ************************************************************************** */
int				has_eaten_enough(t_philo *philosopher);
void			take_forks(t_philo *philosopher);
void			drop_forks(t_philo *philosopher);
int				all_philosophers_are_satisfied(t_dinner *dinner);
int				is_philosopher_dead(t_philo *philosopher);

/* ************************************************************************** */
/*                             Initialization                                 */
/* ************************************************************************** */
int				is_valid_args(int ac, char **av);
int				init_dinner(t_dinner *dinner, int ac, char **av);
int				allocate_philosophers(t_dinner *dinner);
int				init_philosopher(t_philo *philo, int id, t_dinner *dinner);
int				init_monitor(t_monitor *monitor, t_dinner *dinner);
int				init_semaphores(t_monitor *monitor, int total);

/* ************************************************************************** */
/*                                 time                                       */
/* ************************************************************************** */
unsigned int	get_current_time(void);
unsigned int	get_timestamp(unsigned int start_time);
int				msleep(int miliseconds);

/* ************************************************************************** */
/*                                 clean                                      */
/* ************************************************************************** */
void			clean_all(t_dinner *dinner);
void			clean_philosophers(t_dinner *dinner);
void			clean_monitor(t_monitor *monitor);
void			unlink_semaphores(void);
void			kill_all_philosophers(t_dinner  *dinner);
void			wait_all_philosophers(t_dinner *dinner);

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
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isdigit(int c);
void			safe_print(t_philo *philo, char *message);

/* ************************************************************************** */
/*                           Semaphore Names                                  */
/* ************************************************************************** */
# define SEM_FORKS "/forks"
# define SEM_PRINT "/print"
# define SEM_MEALS "/meals"
# define SEM_DEATH "/death"
# define SEM_END "/end"

/* ************************************************************************** */
/*                                Limits                                      */
/* ************************************************************************** */
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define ERROR -1
# define TRUE 1
# define FALSE 0
# define FAIL 0
# define SUCCES 1
# define FINISH 0
# define FREE 1
# define TAKEN 0
# define DEATH 0
# define ALIVE 1
# define HUNGRY 0
# define SATISFYED 1
# define RIP 1
# define YOU_CAN_EAT 1
# define NO_ATRIBUTE 0
# define NO_RETURN_VALUE 0
# define SIMULATION_ENDED 0

/* ************************************************************************** */
/*                                Messages                                    */
/* ************************************************************************** */
# define DIED "died\n"
# define EATING "is eating\n"
# define THINKING "is thinking\n"
# define SLEEPING "is sleeping\n"
# define TAKE_FORK "has taken a fork\n"
# define ERR_ARGS "Usage: ./philo philos(n) die(ms) eat(ms) sleep(ms) [meals]\n"
# define ERR_INT "Error: Arguments must be positive integers (1-2147483647)\n"
# define ERR_MEM "Error: Memory alloc failed. Check system resources\n"
# define ERR_MUTEX_INIT "Error: Failed to initialize mutex\n"
# define ERR_MUTEX_DESTROY "Error: Failed to destroy mutex\n"
# define ERR_FORK "Error: Fork process failed\n"
# define ERR_TIME "Error: Failed to get system time\n"
# define ERR_INIT "Error: Initialization process failed\n"
# define ERR_SIM "Error: Simulation failed during execution\n"
# define ERR_THREAD "Error: Failed to create thread\n"
# define ERR_WAIT "Error: Failed to wait for processes to finish\n"
# define ERR_SLEEP "Error: Sleep function interrupted or failed\n"
# define ERR_MS "Error: Times under 60 ms for die, eat and sleep are not allowed\n"
# define ERR_TOTAL "Error: The dinner can not host more than 200 philosophers\n"
# define ERR_SEM_INIT "Error: Initialization semaphorer process failed\n"
# define DINNER_START "The dinner has started\n"
# define DINNER_SUCCES "All philosophers have eaten enough\n"
# define DINNER_ENDED "The dinner has ended\n"

#endif
