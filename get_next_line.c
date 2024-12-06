/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:45:59 by msuokas           #+#    #+#             */
/*   Updated: 2024/12/06 15:56:56 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

TODO: MAKE THE FUNCTION TO UPDATE THE BUFFER WITH REMOVED REMAINDER

char	*add_to_buff(char *buffer, char *stash)
{
	char	*new_str;

	new_str = ft_strjoin(buffer, stash);
	free(buffer);
	return (new_str);
}
char	*read_text(int fd, char *buffer)
{
	char	*stash;
	size_t	byte_size;

	stash = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!stash)
		return (NULL);
	byte_size = 1;
	while (byte_size > 0)
	{
		if (byte_size == -1)
			return (NULL);
		byte_size = read(fd, stash, BUFFER_SIZE);
		buffer = add_to_buff(buffer, stash);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	free(stash);
	return (buffer);
}
char	*clean_line(char *stash)
{
	int		length;
	int		i;
	char	*cleaned_line;

	length = 0;
	while (stash[length] != '\n' && stash[length] != '\0')
		length++;
	cleaned_line = malloc((length + 1) * sizeof(char));
	if (!cleaned_line)
		return (NULL);
	i = 0;
	while (i < length)
	{
		cleaned_line[i] = stash[i];
		i++;
	}
	cleaned_line[i] = '\0';
	return (cleaned_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_strdup("");
	buffer = read_text(fd, buffer);
	line = clean_line(buffer);

	return (line);
}

int	main(void)
{
	char	*buffer;
	int		i;
	int		fd;

	i = 0;
	fd = open("hello.txt", O_RDONLY);
	buffer = get_next_line(fd);
	if (!buffer)
		return (0);
	while (buffer[i])
	{
		write(1, &buffer[i], 1);
		i++;
	}
	write(1, "\n", 1);
	free(buffer);
	return (0);
}
