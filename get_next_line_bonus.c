/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:58:58 by smiranda          #+#    #+#             */
/*   Updated: 2024/05/11 14:29:30 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*line_buffer[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	line_buffer[fd] = ft_get_buffer(fd, line_buffer[fd]);
	if (!line_buffer[fd])
		return (NULL);
	line = ft_get_line(line_buffer[fd]);
	line_buffer[fd] = ft_get_rest(line_buffer[fd]);
	return (line);
}

char	*ft_get_buffer(int fd, char *line_buffer)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(line_buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(line_buffer);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		line_buffer = ft_strjoin(line_buffer, buffer);
		if (!line_buffer)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (line_buffer);
}

char	*ft_get_line(char *line_buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!line_buffer[i])
		return (NULL);
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
	{
		line[i] = line_buffer[i];
		i++;
	}
	if (line_buffer[i] == '\n')
	{
		line[i] = line_buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_get_rest(char *line_buffer)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	if (!line_buffer[i])
		return (free(line_buffer), NULL);
	rest = (char *)malloc((ft_strlen(line_buffer) - i + 1) * sizeof(char));
	if (!rest)
		return (NULL);
	i++;
	j = 0;
	while (line_buffer[i])
		rest[j++] = line_buffer[i++];
	rest[j] = '\0';
	i = -1;
	while (rest[++i])
		line_buffer[i] = rest[i];
	line_buffer[i] = '\0';
	free(rest);
	return (line_buffer);
}

// int	main(void)
// {
// 	int		fd1, fd2, fd3;
// 	char	*line;
// 	int		count;

// 	count = 1;
// 	fd1 = open("output1.txt", O_RDONLY);
//     fd2 = open("output2.txt", O_RDONLY);
//     fd3 = open("output3.txt", O_RDONLY);
//     while (count)
//     {
//         line = get_next_line(fd1);
//         if (line == NULL)
//             break;
//         count++;
//         printf("[%d]:%s", count, line);
//         free(line);

//         line = get_next_line(fd2);
//         if (line == NULL)
//             break;
//         count++;
//         printf("[%d]:%s", count, line);
//         free(line);

//         line = get_next_line(fd3);
//         if (line == NULL)
//             break;
//         count++;
//         printf("[%d]:%s", count, line);
//         free(line);
//     }
// 	if (fd1 == -1 || fd2 == -1 || fd3 ==-1)
// 	{
// 		printf("Error opening file");
// 		return (1);
// 	}
// 	close(fd1);
//     close(fd2);
//     close(fd3);
// 	return (0);
// }