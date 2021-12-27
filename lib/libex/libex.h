/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:32:44 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/02 11:38:57 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBEX_H
# define LIBEX_H
# include <stdint.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/errno.h>
# include <string.h>
# include <libgen.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
#ifndef TBOOL
# define TBOOL
typedef enum	e_bool
{
	FALSE = 0,
	TRUE
}				t_bool;
#endif
# define SAFE_FREE(p) {free(p); p = NULL;}
# define IS_INF(a) (a == INFINITY || a == -INFINITY)
# define IS_RANGE(n, a, b) (a <= n && n <= b)

char	**ft_split_charset(char *str, char *charset);
char	*ft_strndup(char *str, size_t n);
int		ft_get_next_line(int fd, char **line);
int		ft_isspace(int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strrncmp(const char *s1, const char *s2, size_t n);
int		is_printable(unsigned char c);
t_bool	is_n_char(const char *s, int c, int max);
t_bool	is_n_split(char **ss, size_t n);
t_bool	is_ranges(double array[3], double a, double b);
void	*free_return(char **s, void *ret);
void	free_ss(char ***sss);
#endif
