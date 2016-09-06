/*
** server_cmd_get.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:35:52 2014 lamy_a
** Last update Sun Apr 13 20:36:35 2014 lamy_a
*/

#include <sys/param.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "server.h"

static int	cmd_get_begin_transfere(t_client *client, struct stat *stats,
					char *path)
{
  mode_t	mode;

  mode = stats->st_mode;
  printf("client request file : %s (%lu)\n", path, stats->st_size);
  client->file_size = stats->st_size;
  client->file = fopen(path, "rb");
  client->nb_packet_sent_for_file = 0;
  if (client->file == NULL)
    return (send_packet_info(client, get_perror_buffer(), 1));
  return (send_packet_file_descriptor(client, get_filename(path), mode, 1));
}

int		cmd_get(t_client *client, int ac, char **av)
{
  char		realp[MAXPATHLEN];
  char		newpath[MAXPATHLEN * 2];
  struct stat	stats;

  if (ac != 2)
    return (send_packet_info(client, "ERROR: Usage: get filename\n", 1));
  bzero(newpath, MAXPATHLEN * 2);
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
  if (lstat(newpath, &stats) == -1)
    return (send_packet_info(client, get_perror_buffer(), 1));
  if (!S_ISREG(stats.st_mode) || S_ISLNK(stats.st_mode))
    return (send_packet_info(client, "ERROR: invalid type of file\n", 1));
  return (cmd_get_begin_transfere(client, &stats, newpath));
}
