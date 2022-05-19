/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <thomas.sircus@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 19:42:31 by nthomas-          #+#    #+#             */
/*   Updated: 2021/08/26 19:42:37 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/resource.h>
# define BUFFER_SIZE 20

char	*get_next_line(int fd);
size_t	ft_strlcatt(char *dst, const char *src, size_t dstsize);
size_t	ft_strlenn(const char *s);
void	*ft_memmovee(void *dst, const void *src, size_t len);

#endif
