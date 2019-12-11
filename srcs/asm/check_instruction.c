#include "../../includes/asm.h"

char		*suppr_space(char *line)
{
	char	**res;
	char	*str;
	int	len;
	int	i;

	i = -1;
	len = 0;
	res = ft_split_whitespaces(line);
	while (res[++i] != NULL)
	{
		if (i == 0)
			str = ft_strcat(res[i], " ");
		else
			str = ft_strcat(str, res[i]);
	}
	str = ft_strcat(str, "\0");
	return (str);
}

char		*suppr_space_label(char *line, t_asm *assm)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			;
		else if (line[i] == COMMENT_CHAR)
			return ("\0");
		else if (ft_strchr(LABEL_CHARS, line[i]) != NULL)
		{
			while (ft_strchr(LABEL_CHARS, line[i]) != NULL)
				i++;
			if (line[i] == LABEL_CHAR)
			{
				assm->nb_label++;
				line = line + i + 1;
				i = -1;
			}
			else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
				return (suppr_space(line));
			else
				return (NULL);
		}
		else
			return (NULL);
		i++;
	}
	return ("\0");
}

int		check_params(char **tmp, int i)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (tmp[j] != NULL)
	{
		if (j + 1 > op_tab[i].nb_arg)
			return (-1);
		if ((op_tab[i].args[j] == T_REG || op_tab[i].args[j] == T_REG + T_DIR || op_tab[i].args[j] == T_REG + T_IND || op_tab[i].args[j] == T_REG + T_IND + T_DIR) && check_t_reg(tmp[j]) == 1)
			count = count + 1;
		else if ((op_tab[i].args[j] == T_DIR || op_tab[i].args[j] == T_DIR + T_REG || op_tab[i].args[j] == T_DIR + T_IND || op_tab[i].args[j] == T_DIR + T_REG + T_IND) && check_t_dir(tmp[j]) == 1)
		{
			if (op_tab[i].label == 0)
				count = count + 4;
			else
				count = count + 2;
		}
		else if ((op_tab[i].args[j] == T_IND || op_tab[i].args[j] == T_IND + T_REG || op_tab[i].args[j] == T_IND + T_DIR || op_tab[i].args[j] == T_IND + T_DIR + T_REG) && check_t_ind(tmp[j]) == 1)
			count = count + 2;
		else
			return (-1);
		j++;
	}
	return (count);
}

int		check_line_instruc(char *line)
{
	char	**tmp;
	char	**pmt;
	int	count;
	int	i;

	count = 0;
	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (op_tab[i].nb_arg != 0 && (ft_strcmp(tmp[0], op_tab[i].name) != 0))
		i++;
	if (i > 15)
		return (-1);
	pmt = ft_strsplit(tmp[1], SEPARATOR_CHAR);
	if ((count = check_params(pmt, i)) < 0)
		return (-1);
	count++;
	if (op_tab[i].nb_arg > 1)
		count++;
	return (count);
}

int		check_instruc(int fd, t_asm *assm)
{
	char	*line;
	int	r;
	
	r = 0;
	while (get_next_line(fd, &line))
	{
		if ((line = suppr_space_label(line, assm)) == NULL)
			return (-1);
		if (ft_strcmp("\0", line) == 0)
			;
		else
		{
			if ((r = check_line_instruc(line)) < 0)
				return (-1);
			assm->len_bytes = assm->len_bytes + r;
		}
	}
	return (assm->len_bytes);
}
