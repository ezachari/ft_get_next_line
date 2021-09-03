/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:06:25 by ezachari          #+#    #+#             */
/*   Updated: 2020/11/25 15:59:32 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_freefdb(char **fdb, char *leakfbd)
{
	free(*fdb);
	*fdb = leakfbd;
}

static char	*ft_read_file(int fd, char **fdb)
{
	char	*buffer;
	int		rbyte;
	char	*leakfdb;

	if (!(buffer = (char *)malloc(sizeof(buffer) * (BUFFER_SIZE + 1))))
		return (NULL);
	if ((read(fd, buffer, 0)) == -1)
	{
		free(buffer);
		return (NULL);
	}
	if (*fdb == NULL)
		*fdb = ft_strdup("");
	while (!(ft_strchr(*fdb, '\n')))
	{
		if ((rbyte = read(fd, buffer, BUFFER_SIZE)) < 0)
			return (NULL);
		buffer[rbyte] = '\0';
		leakfdb = ft_strjoin(*fdb, buffer);
		ft_freefdb(fdb, leakfdb);
		if (rbyte == 0)
			break ;
	}
	free(buffer);
	return (*fdb);
}

static int	ft_wr(char *eos, char **line, char **fdbuf, int fd)
{
	char	*leakline;
	char	*leakfd;

	if (!(*line))
	{
		if (!(*line = malloc(1)))
			return (-1);
		*line[0] = '\0';
	}
	leakline = *line;
	*line = ft_substr(fdbuf[fd], 0, eos - fdbuf[fd]);
	free(leakline);
	leakfd = fdbuf[fd];
	fdbuf[fd] = ft_strdup(fdbuf[fd] + (eos - fdbuf[fd]) + 1);
	free(leakfd);
	return (0);
}

static int	ft_elwr(char **line, char **fdbuf, int fd)
{
	char	*leakline;

	if (!(*line))
	{
		if (!(*line = malloc(1)))
			return (-1);
		*line[0] = '\0';
	}
	leakline = *line;
	*line = ft_strdup(fdbuf[fd]);
	free(leakline);
	free(fdbuf[fd]);
	fdbuf[fd] = NULL;
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char		*fdbuf[1024];
	char			*eos;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!(fdbuf[fd] = ft_read_file(fd, &fdbuf[fd])))
		return (-1);
	if (!((*line) = malloc(1)))
		return (-1);
	if ((eos = ft_strchr(fdbuf[fd], '\n')))
	{
		if ((ft_wr(eos, line, fdbuf, fd) < 0))
			return (-1);
		return (1);
	}
	else
	{
		if ((ft_elwr(line, fdbuf, fd) < 0))
			return (-1);
		return (0);
	}
}
