#include "get_next_line.h";

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

int	ft_strlen(char *str)
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
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		total_length;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_length = s1_len + s2_len + 1;
	new_str = ft_calloc(total_length, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_memmove(new_str, s1, s1_len);
	ft_memmove(new_str + s1_len, s2, s2_len);
	return (new_str);
}


