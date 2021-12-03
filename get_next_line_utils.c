#include "get_next_line.h"

size_t	ft_strlen(const char *s)
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		total;
	int		i;

	if(!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = 0;
	}
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


char	*ft_strchr(const char *s, int c)
{
	char	*r;

	r = (char *)s;
	while (*r)
	{
		if (*r == (unsigned char)c)
			return (r);
		r++;
	}
	if (!*r && !c)
		return (r);
	return (NULL);
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
