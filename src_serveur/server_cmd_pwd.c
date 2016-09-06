/*
** server_cmd_pwd.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 19:54:18 2014 lamy_a
** Last update Sun Apr 13 20:04:24 2014 lamy_a
*/

#include <unistd.h>
#include <string.h>
#include "server.h"

int		cmd_pwd(t_client *client, int ac, char **av)
{
  char		pwdstr[PATH_MAX + 1];

  (void)ac;
  (void)av;
  bzero(pwdstr, PATH_MAX + 1);
  strcat(pwdstr, client->path + client->hide_path);
  strcat(pwdstr, "\n");
  if (send_packet_info(client, pwdstr, 0))
    return (1);
  return (send_packet_info(client, "SUCCESS: request\n", 1));
}
