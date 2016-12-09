#include "../42sh/libft/includes/libft.h"
#include <stdio.h>
#define BUFFER_SIZE 1000
#define BRACE_SIZE 1000

typedef			struct	s_brace
{
	char			head[BRACE_SIZE];
	char			tail[BRACE_SIZE];
	char			sub[BRACE_SIZE];
}						t_brace;


/*
 ** Add head and tail to the array of arg. Free the old strings.
 */

static char		**ft_addheadtail(char  **tab, char *head, char *tail)
{
	int		size;
	char	*res;
	char	*tmp;
	int		i;

	i = -1;
	while (tab[++i])
	{
		size = ft_strlen(head);
		res = ft_strjoin(head, tail);
		tmp = res;
		res = ft_strinsert(res, tab[i], &(res[size]));
		ft_freegiveone((void **)&tmp);
		tmp = tab[i];
		tab[i] = res;
		ft_freegiveone((void **)&tmp);
	}
	return (tab);

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
static char		**ft_addtotab(t_brace *b, char **tab, char **res, char inbraces)
{
	char **tmp;

	tmp = tab;
	if (!b->sub[0])
	{
		tab = ft_strtabadd(tab, ft_strdup(b->head));
	}
	else 
	{
		tab = ft_inserttab(tab, ft_addheadtail(res, b->head, b->tail),
		ft_strtablen(tab));
		if (tmp)
			ft_free(res);
	}
	ft_bzero(b, sizeof(t_brace));
	return (tab);
}

char	**ft_braces(char *str, char inbraces)
{
	t_brace	b;
	int		n;
	char	**tab;
	char	**res;
	int		i;

	i = -1;
	tab = NULL;
	ft_bzero(&b, sizeof(t_brace));
	while (*str)
	{
		printf("i = %d\n",++i);
		printf("c = %c\n",*str);
		if (*str == '{' && (n = ft_isbraces(str)))
		{
			res = ft_braces((ft_strncpy(b.sub, str + 1, n - 1)), 1);
			str += n;
		}
		else if (*str == ',' && inbraces)
			tab = ft_addtotab(&b, tab, res, inbraces);
		else if (!(b.sub[0]))
			ft_strncat(b.head, str, 1);
		else 
			ft_strncat(b.tail, str, 1);
		str++;
	}
	if (!inbraces)
		printf("a la sortie negro\n");
	tab = ft_addtotab(&b, tab, res, inbraces);
	return (tab);
}

int main(int ac, char **av)
{
	int		i;
	char	**tab;

	if (ac > 1)
	{
		tab = ft_braces(av[1], 0);
		ft_putstrtab(tab, '\n');
	}
	return (0);
}
