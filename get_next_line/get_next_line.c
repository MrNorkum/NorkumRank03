#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int i;
	for (i = 0; str && str[i]; i++);
	return (i);
}

char	*ft_strjoin(char* str1, char* str2)
{
	char *tmp;

	tmp = (char *)malloc((ft_strlen(str1) + ft_strlen(str2) + 1));

	int i = -1;
	while(str1 && str1[++i])
		tmp[i] = str1[i];

	int j = -1;
	while(str2 && str2[++j])
		tmp[i + j] = str2[j];

	tmp[i + j] = '\0';
	free(str1); free(str2);
	return (tmp);
}

int	check(char *line)
{
	int	i;

	if(line == NULL)
		return (-1);

	i = 0;
	while(line[i])
	{
		if(line[i] == '\n')
			return i;
		i++;
	}
	return (-1);
}

char	*ft_substr(char *str, int i)
{
	int		j;
	char	*new;

	j = -1;
	new = (char *)malloc(i + 1);

	while(str[++j] && j < i)
		new[j] = str[j];

	return (new[j] ='\0', new);
}

char *next_line(int fd,char *s)
{
	char *new;

	int  i = 1;

	while(check(s) < 0 && i > 0)
	{
		new  =(char *)malloc(BUFFER_SIZE + 1);

		i = read(fd, new, BUFFER_SIZE);

		if((!i && !s) || i == -1)
			return (free(new), free(s), NULL);

		new[i] = '\0';

		s = ft_strjoin(s, new);
	}
	return (s);
}

char *get_next_line(int fd)
{
	char	*str, *tmp;
	static char*	line = NULL;

	if(BUFFER_SIZE <= 0 || fd <= -1)
		return (NULL);

	line = next_line(fd, line);
	int i = check(line);

	if(line != NULL)
	{
		if(i != -1)
		{
			tmp = line;
			str = ft_substr(line, i + 1);
			line = ft_substr(&line[i+1], ft_strlen(line) - i);
			free(tmp);
		}
		else
		{
			str = ft_substr(line, ft_strlen(line));
			free(line); line = NULL;
		}
		return(str);
	}
	return (NULL);
}
