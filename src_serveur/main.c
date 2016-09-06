/*
** main.c for myftp in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Mon Apr  7 16:19:46 2014 lamy_a
** Last update Sun Apr 13 20:57:09 2014 lamy_a
*/

#include <stdlib.h>
#include <signal.h>
#include "server.h"

static void	init_handler(t_handler *ptrf)
{
  ptrf[PACKET_CMD] = handle_cmd;
  ptrf[PACKET_DECO] = handle_disconnect;
  ptrf[PACKET_FILEPART] = handle_filepart;
  ptrf[PACKET_FILEINFO] = handle_fileinfo;
  ptrf[PACKET_INFO] = handle_default;
  ptrf[PACKET_PROMPT] = handle_default;
}

int		main(int ac, char **av)
{
  t_handler	ptrf[NBR_PACKET];
  t_cmd_list	*cmd_list;
  int		port;

  cmd_list = NULL;
  if (ac != 2)
    return (my_usage(av[0]));
  port = atoi(av[1]);
  if (port < 0 || port > 65535)
    return (my_error(E_PORT, 0));
  signal(SIGINT, exit_sock);
  init_handler(ptrf);
  init_cmd_list(&cmd_list);
  printf(START_SERVER);
  printf(PORT_SERVER, port);
  return (my_ftp(atoi(av[1]), ptrf, cmd_list));
}
