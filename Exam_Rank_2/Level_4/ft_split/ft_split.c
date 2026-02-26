#include <stdlib.h>
#include <stdio.h>

int ft_spaces(char c){
	return ((c >= 9 && c <= 13) || c == 32);
}

int ft_split_len(char *str){
	int i = 0;
	int len = 0;

	while (str[i])
	{
		while (str[i] && ft_spaces(str[i]))
			i++;
		if (str[i] && !ft_spaces(str[i])){
			len++;
			while (str[i] && !ft_spaces(str[i]))
				i++;
		}
	}
	return (len);
}

int ft_find_word(char *str, int *start, int *end)
{
	int i = *end;
	while (str[i] && ft_spaces(str[i]))
		i++;
	*start = i;
	while (str[i] && !ft_spaces(str[i]))
		i++;
	*end = i;
	return (*start < *end);
}

void ft_copy(int start, int end, char *ptr, char *str)
{
	int i = 0;

	while (start < end)
		ptr[i++] = str[start++];
	ptr[i] = '\0';

}

void ft_free(char **ptr, int word)
{
	int i = 0;
	while (i < word)
		free(ptr[i++]);
	free (ptr);
}
int ft_fill(char **ptr, char*str)
{
	int start = 0;
	int end = 0;
	int word = 0;

	while (ft_find_word(str, &start, &end)){
		ptr[word] = (char *) malloc(end - start + 1);
		if (!ptr[word]){
			ft_free(ptr, word);
			return (0);
		}
		ft_copy(start, end, ptr[word], str);
		word++;
	}
	ptr[word] = NULL;
	return (1);
}

char **ft_split(char *str)
{
	char **result;
	int len = ft_split_len(str);

	result = (char **) malloc((len + 1) * sizeof (char *));
	if (!result)
		return (NULL);
	if (!ft_fill(result, str))
		return (NULL);
	return (result);
}

int main(void)
{
    char **result;
    int i = 0;

    char *test = "   Hello   world  this is   a test  ";

    result = ft_split(test);
    if (!result)
    {
        printf("Split failed\n");
        return (1);
    }

    while (result[i])
    {
        printf("Word %d: [%s]\n", i, result[i]);
        i++;
    }

    // free memory
    i = 0;
    while (result[i])
        free(result[i++]);
    free(result);

    return (0);
}