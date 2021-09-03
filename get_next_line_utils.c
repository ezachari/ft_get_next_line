/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:06:46 by ezachari          #+#    #+#             */
/*   Updated: 2020/11/23 20:06:48 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(d = (char *)malloc(sizeof(*s) * (len + 1))))
		return (NULL);
	if (NULL == s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
		{
			d[j] = s[i];
			j++;
		}
		i++;
	}
	d[j] = '\0';
	return (d);
}

char	*ft_strchr(const char *str, int ch)
{
	const char *s;

	s = str;
	while (*s != '\0')
	{
		if (*s == ch)
			return ((char*)s);
		s++;
	}
	if (*s == ch)
		return ((char*)s);
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	char	*s;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	if (!(s = malloc(len + 1)))
		return (NULL);
	while (str[i] != '\0')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	int		i;
	int		j;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	if (NULL == s1 && NULL == s2)
		return (NULL);
	if (!(temp = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s1[j] != '\0')
		temp[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		temp[i++] = s2[j++];
	temp[i] = '\0';
	return (temp);
}
