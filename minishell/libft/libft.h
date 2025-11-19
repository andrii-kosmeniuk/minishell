/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:11:34 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/09 08:59:37 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <limits.h>

# define BUFFER_SIZE 100

typedef struct s_var
{
	char	*lines_returned;
	ssize_t	read_bytes;
	size_t	i;
	size_t	j;
	size_t	start;
}	t_var;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	size_t			i;
	size_t			j;
	size_t			start;
}	t_list;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t num, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int a);
int		ft_isascii(int d);
int		ft_isdigit(int b);
int		ft_isprint(int e);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
void	free_partial(char **array, size_t count);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *str, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int ab);
int		ft_toupper(unsigned int ch);
int		ft_strcmp(char *s1, char *s2);
size_t	array_len(char **str);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
//printf functions
int		print_char(char c);
int		print_string(char *s);
int		print_d(int d);
int		print_i(int i);
int		print_u(unsigned int u);
int		print_x(unsigned int num);
int		print_x_upper(unsigned int num);
int		print_pointer(unsigned long pointer);
int		print_percent(void);
int		ft_printf(const char *format, ...);
int		ft_formats(va_list args, const char format);
long	ft_atol(const char *str);
//get_next_line functions
char	*print_line(char *stash);
char	*clean_stash(char *stash);
void	*ft_edge_cases(int fd, char *stash, ssize_t *read_bytes);
char	*get_next_line(int fd);
char	*strjoin_free(char *s1, char *s2);
char	*free_stash_if_line_null(char *stash, char *line);
void	free_ptr(void **ptr);

#endif
