/*
** server_init_cmd.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:09:22 2014 lamy_a
** Last update Sun Apr 13 20:23:14 2014 lamy_a
*/

#include <stdlib.h>
#include "server.h"

static void	add_cmd(t_cmd_list **list, const char *cmd,
			t_cmd_handler handler)
{
  t_cmd_list	*node;

  node = malloc(sizeof(*node));
  if (node == NULL)
    {
      my_error("ftp: ERROR: malloc init failed\n", 0);
      exit(EXIT_FAILURE);
    }
  node->name = cmd;
  node->cmd = handler;
  node->next = NULL;
  if (*list == NULL)
    *list = node;
  else
    {
      node->next = *list;
      *list = node;
    }
}

void		init_cmd_list(t_cmd_list **list)
{
  add_cmd(list, "ls", cmd_ls);
  add_cmd(list, "cd", cmd_cd);
  add_cmd(list, "pwd", cmd_pwd);
  add_cmd(list, "quit", cmd_quit);
  add_cmd(list, "exit", cmd_quit);
  add_cmd(list, "get", cmd_get);
  add_cmd(list, "put", cmd_put);
  add_cmd(list, "help", cmd_help);
}
