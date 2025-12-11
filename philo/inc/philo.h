/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:07:57 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/11 13:11:43 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <signal.h>
# include <stdio.h>
# include <libc.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

// Codes for error tracking
// Successful execution
# define SUCCESS 1
// Unsuccessful execution
# define FAIL 0

typedef struct s_philo
{
  uint32_t  x;
  uint32_t  ate;
} t_philo;

typedef struct s_vars
{
  uint32_t  n;
  uint32_t  die;
  uint32_t  eat;
  uint32_t  sleep;
  uint32_t  fed;
  sig_atomic_t  i;
  pthread_t *t;
  sig_atomic_t	*f;
  pthread_mutex_t m;
} t_vars;

// philo

// Initialisation
bool	valid_input(char **argv);
bool	parse_args(t_vars *p, char **argv);

// Utilities
int	    ft_isdigit(int c);
int	    ft_issign(int c);
int	    ft_isspace(int c);
bool	ft_naun(const char *nptr);
bool	ft_atoui(unsigned int *nbr, const char *nptr);

#endif
