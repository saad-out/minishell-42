/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../../inc/libs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:32:08 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/01 08:32:58 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_H
# define LIBS_H
# include <string.h>

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_tolower(int c);
int		ft_isalnum(int c);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strndup(const char *str, int n);
void    *ft_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif
