/*
** server_cmd_ls.c for cmd_ls in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:00:28 2014 lamy_a
** Last update Sun Apr 13 21:06:58 2014 lamy_a
*/

#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/param.h>
#include <stdlib.h>
#include "server.h"

static int	send_packet_ls(t_client *client, char *path)
{
  DIR		*dir;
  struct dirent	*file;
  char		buffersnd[PACKET_DATA_SIZE];
  char		*format_file;
  int		needsend;

  needsend = 0;
  bzero(buffersnd, PACKET_DATA_SIZE);
  if ((dir = opendir(path)) != NULL)
    while ((file = readdir(dir)) != NULL)
      {
	format_file = get_format_file(path, file);
	if (strlen(format_file) + strlen(buffersnd) > PACKET_DATA_SIZE - 2)
	  {
	    if (send_packet_info(client, buffersnd, 0))
	      return (1);
	    bzero(buffersnd, PACKET_DATA_SIZE);
	  }
	strcat(buffersnd, format_file);
	needsend = 1;
      }
  if (needsend)
    if (send_packet_info(client, buffersnd, 0))
      return (1);
  return (0);
}

int		cmd_ls(t_client *client, int ac, char **av)
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
	  strncmp(client->root_path, realp, strlen(client->root_path) - 1) != 0)
	return (send_packet_info(client, "ERROR: Permission denied\n", 1));
    }
  else
    strcpy(realp, client->path);
  if (send_packet_ls(client, realp))
    return (1);
  return (send_packet_info(client, "SUCCESS: List folder\n", 1));
}
