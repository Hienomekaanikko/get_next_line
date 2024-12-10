/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:45:59 by msuokas           #+#    #+#             */
/*   Updated: 2024/12/10 14:08:02 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*add_to_buff(char *buffer, char *stash)
{
	size_t	buffer_len;
	size_t	stash_len;
	char	*new_str;

	buffer_len = ft_strlen(buffer);
	stash_len = ft_strlen(stash);
	new_str = malloc((buffer_len + stash_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, buffer, buffer_len);
	ft_memcpy(new_str + buffer_len, stash, stash_len + 1);
	free(buffer);
	return (new_str);
}

static char	*read_text(int fd, char *buffer)
{
	char	*stash;
	ssize_t	bytes_read;

	stash = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!stash)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!ft_strchr(buffer, '\n')))
	{
		bytes_read = read(fd, stash, BUFFER_SIZE);
		if (bytes_read < 1)
			break ;
		stash[bytes_read] = '\0';
		buffer = add_to_buff(buffer, stash);
	}
	free(stash);
	return (buffer);
}

static char	*set_buff(char *buffer)
{
	char		*temp;
	size_t		i;
	size_t		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	temp = malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (!temp)
	{
		free (buffer);
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

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
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
	buffer = set_buff(buffer);
	return (line);
}
