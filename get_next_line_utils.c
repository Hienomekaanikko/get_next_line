#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*to;
	unsigned char	*from;

	if (!dest && !src)
		return (NULL);
	to = (unsigned char *)dest;
	from = (unsigned char *)src;
	if (from < to && to < from + n)
		while (n--)
			to[n] = from[n];
	else
		while (n--)
			*(to++) = *(from++);
	return (dest);
}

void *ft_memset(void *dest, int x, size_t n)
{
	char *temp;
	int	i;

	temp = dest;
	i = 0;
	while (n > 0)
	{
		temp[i] = x;
		n--;
		i++;
	}
	return (void *)dest;
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return(i);
}

void	*ft_calloc(size_t count, size_t size)
{
	char		*ptr;

	if (count != 0 && size != 0 && count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		size;
	int		i;

	size = ft_strlen(s);
	ptr = malloc(1 + size * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	*ft_memcpy(void *to, const void *from , size_t n)
{
	const char *from_temp;
	char *to_temp;
	int	i;

	from_temp = from;
	to_temp = to;
	i = 0;
	while (n > 0)
	{
		to_temp[i] = from_temp[i];
		n--;
		i++;
	}
	return (0);
}
