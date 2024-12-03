#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char *join_to_buf(char *result, char *buffer)
{
	char *new;
	size_t result_len, buffer_len;

	if (!result)
		return ft_strdup(buffer);
	if (!buffer)
		return NULL;
	result_len = ft_strlen(result);
	buffer_len = ft_strlen(buffer);
	new = malloc(sizeof(char) * (result_len + buffer_len + 1));
	if (!new)
		return NULL;
	ft_memcpy(new, result, result_len);
	ft_memcpy(new + result_len, buffer, buffer_len);
	new[result_len + buffer_len] = '\0';
	free(result);
	return new;
}

char *get_line(int fd, char *result)
{
	char *buffer;
	int byte_count;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return NULL;
	byte_count = 1;
	while (byte_count > 0)
	{
		byte_count = read(fd, buffer, BUFFER_SIZE);
		if (byte_count == -1)
		{
			free(buffer);
			return NULL;
		}
		buffer[byte_count] = '\0';
		result = join_to_buf(result, buffer);
		if (!result || ft_strchr(buffer, '\n'))
		break;
	}
	free(buffer);
	return result;
}

char *clean_line(char *line)
{
	char *cleaned_line;
	int i;

	if (!line)
		return NULL;
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	cleaned_line = malloc((i + 2) * sizeof(char));
	if (!cleaned_line)
		return NULL;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		cleaned_line[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		cleaned_line[i] = '\n';
		i++;
	}
	cleaned_line[i] = '\0';
	return cleaned_line;
}

char *remove_first_line(char *buffer)
{
	char *new_buffer;
	int i, j;

	if (!buffer)
		return NULL;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return NULL;
	}
	new_buffer = malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (!new_buffer)
	{
		free(buffer);
		return NULL;
	}
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return new_buffer;
}

char *get_next_line(int fd)
{
	static char *buffer;
	 char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	buffer = get_line(fd, buffer);
	if (!buffer)
		return NULL;
	line = clean_line(buffer);
	buffer = remove_first_line(buffer);
	return line;
}
