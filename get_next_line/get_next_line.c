/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:47:38 by ael-bako          #+#    #+#             */
/*   Updated: 2022/11/01 11:04:51 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *str)
{
	char	*buffer;
	int		readed;

	if (!str)
		str = ft_strdup("");
	// printf("%s\n",str);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	readed = 1;
	while (readed != 0 && !ft_strchr(buffer, '\n'))
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		// printf("%s\n",buffer);
		if (readed == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[readed] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*ft_save(char *str)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	// printf("%s\n",str);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!s)
		return (NULL);
	i++;
	c = 0;
	while (str[i])
		s[c++] = str[i++];
	s[c] = '\0';
	free(str);
	return (s);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_read(fd, str);
	if (!str)
		return (NULL);
	line = ft_get_line(str);
	str = ft_save(str);
	return line;
}

// int main()
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	char *str;
// 	str = get_next_line(fd);
// 	printf("::::%s:::\n",str);
// 	// get_next_line(fd);
// 	str = get_next_line(fd);
// 	printf("::::%s:::\n",str);
// 	str = get_next_line(fd);
// 	printf("::::%s:::\n",str);
// 	printf("::::%d:::",fd);
// 	// system("leaks a.out");
// }