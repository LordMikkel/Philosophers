/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:51:24 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/03 02:08:31 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	put_str_fd(int fd, char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		if (write(fd, s, 1) == -1)
			return ;
		s++;
	}
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	if (!nptr)
		return (0);
	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = (result * 10) + (nptr[i++] - '0');
	return (result * sign);
}

bool	ft_atoi_range(const char *nptr)
{
	int			i;
	int			sign;
	long long	result;

	if (!nptr)
		return (0);
	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		if ((sign * result) > INT_MAX || (sign * result) < INT_MIN)
			return (false);
		i++;
	}
	return (true);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*ptr;
	size_t		total_size;
	size_t		i;
	char		*char_ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		return (ptr);
	}
	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	total_size = (nmemb * size);
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	char_ptr = (char *)ptr;
	i = 0;
	while (i < total_size)
	{
		char_ptr[i] = 0;
		i++;
	}
	return (ptr);
}

void	thinks(t_philo *philosopher)
{
	int	think_time;

	safe_print(philosopher, THINKING);
	think_time = philosopher->dinner->dead - philosopher->dinner->eat
		- philosopher->dinner->sleep;
	if (think_time > 0)
		msleep(think_time / 2);
}
