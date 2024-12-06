/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:45:59 by msuokas           #+#    #+#             */
/*   Updated: 2024/12/06 13:38:58 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*add_to_curr(char *buffer, char *stash)
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
	byte_size = 1;
	while (byte_size > 0)
	{
		byte_size = read(fd, stash, BUFFER_SIZE);
		buffer = add_to_curr(buffer, stash);
		if (ft_strchr(stash, '\n'))
		{
			stash[byte_size] = '\0';
			break ;
		}
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_strdup("");
	buffer = read_text(fd, buffer);
}

int	main(void)
{
	char	*buffer;
	int		i;
	int		fd;

	i = 0;
	fd = open("hello.txt", O_RDONLY);
	buffer = get_next_line(fd);

	while (buffer[i])
	{
		write(1, &buffer[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
