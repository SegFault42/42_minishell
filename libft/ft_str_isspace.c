#include "./includes/libft.h"

bool	ft_str_isspace(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (true);
		++i;
	}
	return (false);
}
