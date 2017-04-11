#include "./includes/libft.h"

bool	ft_str_isalpha(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < 'A' && str[i] > 'Z') || (str[i] < 'a' && str[i] > 'z'))
			return (false);
		++i;
	}
	return (true);
}
