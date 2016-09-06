/*
** server_cmd_cd.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 19:56:14 2014 lamy_a
** Last update Sun Apr 13 21:00:46 2014 lamy_a
*/

#include <string.h>
#include <unistd.h>
#include <sys/param.h>
#include <stdlib.h>
#include "server.h"

static int	do_chdir(t_client *client, char *realp)
{
  if (chdir(realp))
    return (send_packet_info(client, get_perror_buffer(), 1));
  bzero(client->path, PATH_MAX);
  getcwd(client->path, PATH_MAX);
  if (client->path[client->hide_path] == '\0')
    client->path[client->hide_path] = '/';
  chdir(client->root_path);
  return (send_packet_info(client, "SUCCESS: Current folder is changed\n", 1));
}

int		cmd_cd(t_client *client, int ac, char **av)
{
  char		realp[MAXPATHLEN];
  char		newpath[MAXPATHLEN * 2];

  bzero(newpath, MAXPATHLEN * 2);
  bzero(realp, MAXPATHLEN);
  newpath[0] = '\0';
  if (ac == 2)
    {
      if (av[1][0] == '/')
	strcat(newpath, client->root_path);
      else
	strcat(newpath, client->path);
      strcat(newpath, "/");
      strcat(newpath, av[1]);
      if (realpath(newpath, realp) == NULL)
	return (send_packet_info(client, get_perror_buffer(), 1));
      if (strlen(realp) < strlen(client->root_path) - 1 ||
	  strncmp(realp, client->root_path, strlen(client->root_path) - 1) != 0)
	return (send_packet_info(client, "ERROR: Permission denied\n", 1));
    }
  else
    strcpy(realp, client->root_path);
  return (do_chdir(client, realp));
}
