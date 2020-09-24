/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:49:23 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/18 00:09:03 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

typedef struct		s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);

int					ft_isblank(const char c);
int					is_blank_line(const char *s);
int					ft_atoi(const char *nptr);
char				*skip_(int flag, char *str);

size_t				ft_strlen(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strndup(char *str, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);

int					ft_lstsize(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstnew(char *content);

#endif
