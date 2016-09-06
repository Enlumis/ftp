/*
** client_handle_fileinfo.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 18:57:49 2014 lamy_a
** Last update Sun Apr 13 21:39:57 2014 lamy_a
*/

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "client.h"

static int	file_isexist(t_client *client, t_file_layer *flayer)
{
  struct stat	stats;
  mode_t	mode;

  client->file = fopen(flayer->file_name, "rb");
  if (client->file != NULL)
    {
      if (lstat(flayer->file_name, &stats) == -1)
	{
	  my_error("ERROR: lstat", 1);
	  return (send_packet_file_descriptor(client, "", 0, 0));
	}
      mode = stats.st_mode;
      return (send_packet_file_descriptor(client, flayer->file_name, mode, 1));
    }
  else
    my_error("ERROR: fopen", 1);
  return (send_packet_file_descriptor(client, "", 0, 0));
}

static int	file_begin_transfere(t_client *client, t_file_layer *flayer)
{
  if (strlen(flayer->file_name) > 0)
    {
      client->file = fopen(flayer->file_name, "wb");
      if (client->file != NULL)
	{
	  bzero(client->file_name, PACKET_DATA_SIZE);
	  strcat(client->file_name, flayer->file_name);
	  printf("%s: Downloading ...\n", client->file_name);
	  if (fchmod(fileno(client->file), flayer->mode))
	    my_error("ERROR: Failed to set file permissions\n", 0);
	}
      else
	my_error("ERROR: open", 1);
    }
  else
    my_error("ERROR: no name file\n", 0);
  return (0);
}

int		handle_fileinfo(t_client *client, t_packet *packet)
{
  t_file_layer	*file_layer;

  file_layer = (t_file_layer*)packet->data;
  if (file_layer->type == FILELAYER_PUT_ISEXIST)
    return (file_isexist(client, file_layer));
  else if (file_layer->type == FILELAYER_GET_BEGIN)
    return (file_begin_transfere(client, file_layer));
  else if (file_layer->type == FILELAYER_GET_END && client->file != NULL)
    {
      fclose(client->file);
      client->file = NULL;
      printf("\n[100%%]\n%s: is done\n", client->file_name);
    }
  return (0);
}
