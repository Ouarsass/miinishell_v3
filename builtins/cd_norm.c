
#include "../minishell.h"

t_list  *cd_norm(t_list *list, t_pi pi, int *st)
{
    char    path[255];
    char    *home;
    t_cd    ci;
    char    **tab;
    char    *old_cur;

    ci.st = &st[0];
	getcwd(path, 255);
	old_cur = ft_strdup(path);
	home = env_value("HOME", list);
	tab = (char **)malloc(sizeof(char *) * 3);
	tab[0] = "cd";
	tab[1] = home;
	tab[2] = NULL;
	ci.i = chdir((const char *)home);
	ci.old_cur = old_cur;
	list = change_dir(tab, ci, list, pi);
	free(home);
	free(tab);
	free(old_cur);
	return (list);
}

void	change_dir_norm(t_cd ci, t_list *list, t_pi pi)
{
	char	path[255];
	char	*current;
	char	**tab;


	tab = (char **)malloc(sizeof(char *) * 3);
	current = ft_strjoin("OLDPWD=", ci.old_cur);
	tab[0] = "export";
	tab[1] = current;
	tab[2] = NULL;
	list = ft_export(tab, list, pi);
	free(current);
	getcwd(path, 255);
	current = ft_strjoin("PWD=", path);
	tab[0] = "export";
	tab[1] = current;
	tab[2] = NULL;
	list = ft_export(tab, list, pi);
	free(current);
	free(tab);
	// free(ci.old_cur);
}