/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjohnnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:09:19 by tjohnnie          #+#    #+#             */
/*   Updated: 2021/01/15 20:09:22 by tjohnnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			ft_free(char *str, int answer)
{
	free(str);
	return (answer);
}

static char			*ft_ostatok(char *stat, char **line)
{
	char			*ostatok;

	ostatok = 0;
	if (stat)
	{
		if ((ostatok = ft_strchr(stat, '\n')))
		{
			*ostatok++ = '\0';
			*line = ft_strdup(stat);
			ft_strlcpy(stat, ostatok, ft_strlen(ostatok) + 1);
		}
		else
		{
			*line = ft_strdup(stat);
			free(stat);
		}
	}
	else
		*line = ft_strdup("");
	return (ostatok);
}

int					get_next_line(int fd, char **line)
{
	static char		*stat[1024];
	int				r;
	char			*str;
	char			*ostatok;

	if (fd == -1 || BUFFER_SIZE < 1 || !line ||
	!(str = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	ostatok = ft_ostatok(stat[fd], line);
	while (!ostatok && (r = read(fd, str, BUFFER_SIZE)))
	{
		if (r == -1)
			return (ft_free(str, -1));
		str[r] = '\0';
		if ((ostatok = ft_strchr(str, '\n')))
		{
			*ostatok++ = '\0';
			stat[fd] = ft_strdup(ostatok);
		}
		*line = ft_strjoin(*line, str);
	}
	if (ostatok)
		return (ft_free(str, 1));
	return (ft_free(str, 0));
}
