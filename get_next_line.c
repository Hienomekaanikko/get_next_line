/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:45:59 by msuokas           #+#    #+#             */
/*   Updated: 2024/12/16 16:25:21 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_text(int fd, char *buffer)
{
	char	*stash;
	int		bytes_read;

	stash = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!stash)
		return (NULL);
	bytes_read = 1;
	while (buffer && bytes_read > 0 && (!ft_strchr(buffer, '\n')))
	{
		bytes_read = read(fd, stash, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		stash[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, stash);
	}
	free(stash);
	return (buffer);
}

static int	count_len(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	return (i);
}

static char	*set_buff(char *buffer, int *sign)
{
	char		*temp;
	size_t		i;
	size_t		j;

	i = count_len(buffer);
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	temp = malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (!temp)
	{
		*sign = 0;
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		temp[j++] = buffer[i++];
	temp[j] = '\0';
	free(buffer);
	return (temp);
}

static char	*clean_line(char *buffer)
{
	size_t		i;
	char		*line;

	i = count_len(buffer);
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			sign;

	sign = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	buffer = read_text(fd, buffer);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = clean_line(buffer);
	buffer = set_buff(buffer, &sign);
	if (sign == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
