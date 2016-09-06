/*
** server_handle_cmd.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 19:44:41 2014 lamy_a
** Last update Sun Apr 13 19:46:18 2014 lamy_a
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

static int		count_args(char *cmd)
{
  int			i;
  int			newarg;
  int			count;

  i = 0;
  newarg = 1;
  count = 0;
  while (cmd[i] != '\0')
    {
      if (cmd[i] == '\t' || cmd[i] == ' ')
	newarg = 1;
      else if (newarg)
	{
	  count++;
	  newarg = 0;
	}
      i++;
    }
  if (newarg && i > 0)
    count++;
  return (count);
}

static int		parse_cmd(char *cmd, char ***av, int *ac)
{
  int			pos;
  char			*word;

  pos = 0;
  *ac = count_args(cmd) + 1;
  *av = malloc(sizeof(**av) * (*ac + 1));
  if (*av == NULL)
    return (1);
  word = strtok(cmd, "\t ");
  while (word != NULL)
    {
      av[0][pos] = strdup(word);
      if (av[0][pos] == NULL)
	return (1);
      pos++;
      word = strtok(NULL, "\t ");
    }
  av[0][pos] = NULL;
  *ac = *ac - 1;
  return (0);
}

static void		free_args(int ac, char **av)
{
  int			i;

  i = 0;
  while (i < ac)
    free(av[i++]);
  free(av);
}

static int		do_command(t_client *client, int ac, char **av)
{
  t_cmd_list		*list;

  list = client->cmd_list;
  while (list != NULL && ac > 0)
    {
      if (strcmp(av[0], list->name) == 0)
	return ((*list->cmd)(client, ac, av));
      list = list->next;
    }
  if (list == NULL || ac == 0)
    {
      if (send_packet_info(client, "ERROR: Command not found\n", 1))
	return (1);
    }
  return (0);
}

int			handle_cmd(t_client *client, t_packet *packet)
{
  char			**av;
  int			ac;
  int			retur;

  if (packet->data[PACKET_DATA_SIZE - 1] != '\0')
    return (my_error("ftp: ERROR: command is too long\n", 0));
  if (parse_cmd((char*)packet->data, &av, &ac))
    return (my_error("ftp: ERROR: malloc args\n", 0));
  retur = do_command(client, ac, av);
  free_args(ac, av);
  return (retur);
}
