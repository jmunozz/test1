#include "../42sh/libft/includes/libft.h"
#include <stdio.h>
#define SIZE 1000

typedef		struct	s_brace
{
					t_list	*all;
					t_list	*arg1;
					t_list	*arg2;
					char	sub[SIZE];
					int		size;
}					t_brace;

void	ft_printlist(t_list *list)
{
	ft_putendl("Impression dea liste");
	while (list)
	{
		printf("%s\n", list->data);
		list = list->next;
	}
}

/*
 ** If the brace is closed later, return the index of closing brace.
 ** If not, return 0.
 */

static int				ft_isbraces(char *str)
{
	int		open;
	int		close;
	int		i;

	open = 0;
	close = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '{')
			open++;
		if (str[i] == '}')
			close++;
		if (open == close)
			return (i);
	}
	return (0);
}


static void		ft_catlist(t_list **arg, char *str)
{
	t_list *list;

	if (!*arg)
		*arg = ft_lstnew(ft_strnew(SIZE), 0);
	list = *arg;
	while (list)
	{
		list->data = ft_strncat(list->data, str, 1);
		list = list->next;
	}
}

static t_list		*ft_distriblist(t_list *list1, t_list *list2)
{
	t_list	*list3;
	t_list	*l;
	t_list	*kill1;
	t_list	*kill2;

	kill1 = list1;
	kill2 = list2;
	list3 = NULL;
	if (!list1)
		return (list2);
	while (list1)
	{
		l = list2;
		while (l)
		{
			ft_list_push_back(&list3, ft_lstnew(ft_strjoin(list1->data, l->data), 0));
			l = l->next;
		}
		list1 =list1->next;
	}
	ft_lstdel(&kill1, &ft_list_free_data);
	ft_lstdel(&kill2, &ft_list_free_data);
	return (list3);
}

/*
** Checks char by char if we enter new braces and call again function in that
** case. Merge argument lists. Concatenate parts of an argument.
*/

t_list		*ft_list(char *str, char out)
{
	t_brace		b;
	
	ft_bzero(&b, sizeof(t_brace));
	while (*str)
	{
		if (*str == ',' && !out)
		{
			ft_list_merge(&(b.all), b.arg1);
			b.arg1 = NULL;
		}
		else if (*str == '{'  && (b.size = ft_isbraces(str)))
		{
			b.arg2 = ft_list(ft_strncpy(b.sub, str + 1, b.size - 1), 0);
				return (NULL);
			b.arg1 = (b.arg1) ? ft_distriblist(b.arg1, b.arg2) : b.arg2;
			ft_bzero(b.sub, SIZE);
			str += b.size;
		}
		else
			ft_catlist(&(b.arg1), str);
		str++;
	}
	ft_list_merge(&(b.all), b.arg1);
	return (b.all);
}

int			main(int ac, char **av)
{
	t_list *list;
	t_list	*tmp;

	list = NULL;
	if (ac > 1)
	{

		list = ft_list(av[1], 1);
		tmp = list;
		if (list)
		{
			while (list)
			{
				printf("%s\n",list->data);
				list = list->next;
			}
			ft_lstdel(&tmp, &ft_list_free_data);
		}
		else
			printf("La liste est nulle.\n");
	}
	return (0);
}
