/*
** src_client for ftp in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Thu Apr 10 17:41:35 2014 lamy_a
** Last update Sun Apr 13 19:08:03 2014 lamy_a
*/

#include <stdlib.h>
#include <signal.h>
#include "client.h"

int	main(int ac, char **av)
{
  int	port;

  if (ac != 3)
    return (my_usage(av[0]));
  port = atoi(av[1]);
  if (port < 0 || port > 65535)
    return (my_error("%s\n", 0, E_PORT));
  signal(SIGINT, exit_client);
  return (my_ftp(av[1], atoi(av[2])));
}
