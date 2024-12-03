#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *to, const void *from , size_t n);

#endif
