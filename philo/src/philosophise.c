/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:13:48 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/14 12:36:52 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_init(t_philo *p, t_data *v);
static int	num_fetch(t_philo *p, t_data *v);
static int	did_you_starve(t_philo *p, t_data *v);
static int	you_died(t_philo *p, t_data *v, struct timeval time);
static void	*philo_exit(t_philo *p);

static void	*philo_exit(t_philo *p)
{
	pthread_mutex_destroy(&p->lock_l);
	pthread_mutex_destroy(&p->lock_r);
	return (0);
}

void	*philosophise(void *data)
{
	t_data			*v;
	t_philo			p;
	int				flag;

	v = data;
	if (!philo_init(&p, v))
		return (0);
	while (1)
	{
		if (v->end == true || (p.meals >= v->fed && v->fed > 0)
			|| did_you_starve(&p, v))
			return (philo_exit(&p));
		if (v->end == false && *p.fork_l == false && *p.fork_r == false)
		{
			flag = go_eat(&p, v);
			if (flag == FAIL)
				return (philo_exit(&p));
		}
	}
	return (0);
}

static bool	philo_init(t_philo *p, t_data *v)
{
	struct timeval	time;

	if (!num_fetch(p, v))
		return (false);
	p->meals = 0;
	p->fork_l = &v->f[p->x - 1];
	if (p->x == v->n)
		p->fork_r = &v->f[0];
	else
		p->fork_r = &v->f[p->x];
	if (gettimeofday(&time, NULL) == -1)
		return (false);
	p->ate_s = time.tv_sec;
	p->ate_u = time.tv_usec;
	if (pthread_mutex_init(&p->lock_l, NULL))
		return (false);
	if (pthread_mutex_init(&p->lock_r, NULL))
	{
		pthread_mutex_destroy(&p->lock_l);
		return (false);
	}
	return (true);
}

static int	num_fetch(t_philo *p, t_data *v)
{
	if (pthread_mutex_lock(&v->m))
		return (FAIL);
	p->x = v->i++;
	if (pthread_mutex_unlock(&v->m))
		return (FAIL);
	return (SUCCESS);
}

static int	you_died(t_philo *p, t_data *v, struct timeval time)
{
	if (pthread_mutex_lock(&v->m))
		return (ERROR);
	printf("%ld%06u %u died\n", time.tv_sec, time.tv_usec, p->x);
	v->end = true;
	if (pthread_mutex_unlock(&v->m))
		return (ERROR);
	return (SUCCESS);
}

static int	did_you_starve(t_philo *p, t_data *v)
{
	struct timeval	time;
	time_t			sec_diff;
	uint32_t		elapsed;

	if (gettimeofday(&time, NULL) == -1)
		return (ERROR);
	sec_diff = time.tv_sec - p->ate_s;
	if (sec_diff > UINT_MAX / USEC_PER_SEC)
		return (you_died(p, v, time));
	elapsed = (sec_diff * USEC_PER_SEC) + (time.tv_usec - p->ate_u);
	if (elapsed > v->die)
		return (you_died(p, v, time));
	return (FAIL);
}
