#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		length;

	length = ft_strlen(s1);
	res = malloc(sizeof(char) * length + 1);
	if (!res)
		return (NULL);
	while (*s1)
	{
		*res = *s1;
		res++;
		s1++;
	}
	*res = 0;
	return (res - length);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*p;
	int		total;
	int		i;

	total = (ft_strlen(s1) + ft_strlen(s2));
	p = malloc(sizeof(char) * (total + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		*p = s1[i];
		i++;
		p++;
	}
	i = 0;
	while (s2[i])
	{
		*p = s2[i];
		i++;
		p++;
	}
	*p = '\0';
	return (p - total);
}


size_t		ft_strchr(const char *s, int c)
{
	char	*r;
	size_t	res;

	res = 0;
	r = (char *)s;
	while (r[res])
	{
		if (r[res] == (unsigned char)c)
			return (res);
		res++;
	}
	if (!*r && !c)
		return (0);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	slen;
	size_t	i;

	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	if (slen <= len)
		len = slen;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}
