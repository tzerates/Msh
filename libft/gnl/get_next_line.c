/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:22:58 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/15 16:30:00 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	scan_nl(char *s)
{
	int	pos;

	pos = 0;
	while (s && s[pos])
	{
		if (s[pos] == '\n')
			return (pos);
		pos++;
	}
	return (-1);
}

static char	*strjoin_eol(char *s, char *buf)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	while (buf && buf[j] && buf[j] != '\n')
		j++;
	tab = (char *)malloc(i + j + 1);
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s && s[i] && s[i] != '\n')
		tab[j++] = s[i++];
	while (buf && *buf && *buf != '\n')
		tab[j++] = *buf++;
	tab[j] = 0;
	free(s);
	return (tab);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buf[BUFFER_SIZE + 1];
	int			i;
	int			ret;

	i = 0;
	ret = 1;
	line = strjoin_eol(NULL, buf);
	if (!line)
		return (NULL);
	while (scan_nl(buf) == -1 && ret && ret != -1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = 0;
		line = strjoin_eol(line, buf);
		if (!line)
			return (NULL);
	}
	if (!buf[0])
		return (NULL);
	ret = scan_nl(buf) + 1;
	while (buf[ret] && buf[i])
		buf[i++] = buf[ret++];
	buf[i] = 0;
	return (line);
}
