#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_dinner t_dinner;
typedef struct s_philosopher t_philosopher;
typedef struct s_monitor t_monitor;

struct s_dinner {
	unsigned int	num_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				max_meals;
	unsigned int	start_time;
	int				simulation_ended;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;
	t_philosopher	*philosophers;
	t_monitor		*monitor;
};

struct s_philosopher {
	int				id;
	unsigned int	times_eaten;
	unsigned int	last_meal_time;
	pthread_t		thread;			// Thread movido aquí
	pthread_mutex_t	meal_mutex;
	t_dinner		*dinner;
};

struct s_monitor {
	pthread_mutex_t	service_mutex;
	int				*forks_available;
	pthread_t		monitor_thread;
	t_dinner		*dinner;
};


int	is_philosopher_dead(t_philosopher *philo)
{
	unsigned int	current_time;
	unsigned int	time_since_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	current_time = get_timestamp(philo->dinner);
	time_since_meal = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);

	return (time_since_meal >= philo->dinner->time_to_die);
}

int	wait_for_forks(t_philosopher *philo)
{
	while (!philo->dinner->simulation_ended)
	{
		if (request_forks(philo->dinner->monitor, philo->id))
			return (1);
		usleep(100);
		if (is_philosopher_dead(philo))
		{
			announce_death(philo);
			return (0);
		}
	}
	return (0);
}


int	all_philosophers_satisfied(t_dinner *dinner)
{
	unsigned int	i;

	if (dinner->max_meals <= 0)
		return (0);

	i = 0;
	while (i < dinner->num_philosophers)
	{
		if (!has_eaten_enough(&dinner->philosophers[i]))
			return (0);
		i++;
	}
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;

	if (philo->dinner->num_philosophers == 1)
	{
		safe_print(philo, "has taken a fork");
		usleep(philo->dinner->time_to_die * 1000);
		return (NULL);
	}

	if (philo->id % 2 == 0)
		usleep(philo->dinner->time_to_eat * 500);

	while (!philo->dinner->simulation_ended)
	{
		safe_print(philo, "is thinking");

		if (!wait_for_forks(philo))
			return (NULL);

		safe_print(philo, "has taken a fork");
		safe_print(philo, "has taken a fork");
		safe_print(philo, "is eating");

		eat_meal(philo);
		usleep(philo->dinner->time_to_eat * 1000);
		return_forks(philo->dinner->monitor, philo->id);

		if (has_eaten_enough(philo))
			break ;

		safe_print(philo, "is sleeping");
		usleep(philo->dinner->time_to_sleep * 1000);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_monitor		*monitor;
	unsigned int	i;

	monitor = (t_monitor *)arg;

	while (!monitor->dinner->simulation_ended)
	{
		i = 0;
		while (i < monitor->dinner->num_philosophers)
		{
			if (is_philosopher_dead(&monitor->dinner->philosophers[i]))
			{
				announce_death(&monitor->dinner->philosophers[i]);
				return (NULL);
			}
			i++;
		}

		if (all_philosophers_satisfied(monitor->dinner))
		{
			pthread_mutex_lock(&monitor->dinner->end_mutex);
			monitor->dinner->simulation_ended = 1;
			pthread_mutex_unlock(&monitor->dinner->end_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;

	if (!valid_arguments(argc, argv))
	{
		printf("Usage: %s philosophers die_time eat_time sleep_time [max_meals]\n", argv[0]);
		return (1);
	}

	dinner = (t_dinner){0};

	if (!setup_dinner(&dinner, argc, argv))
	{
		cleanup_dinner(&dinner);
		return (1);
	}

	if (!start_threads(&dinner))
	{
		cleanup_dinner(&dinner);
		return (1);
	}

	wait_for_threads(&dinner);
	cleanup_dinner(&dinner);
	return (0);
}
