/*
** server_handle_fileinfo.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:49:58 2014 lamy_a
** Last update Sun Apr 13 21:05:20 2014 lamy_a
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/param.h>
#include "server.h"

static int	file_put_begin(t_client *client, t_file_layer *flayer)
{
  char		path[MAXPATHLEN * 2];

  if (strlen(get_filename(flayer->file_name)) > 0)
    {
      bzero(path, MAXPATHLEN * 2);
      strcat(path, client->path);
      strcat(path, "/");
      strcat(path, get_filename(flayer->file_name));
      client->file = fopen(path, "wb");
      if (client->file != NULL)
	{
	  printf("Upload: %s\n", path);
	  if (fchmod(fileno(client->file), flayer->mode))
	    return (send_packet_info(client, get_perror_buffer(), 1));
	}
      else
	return (send_packet_info(client, get_perror_buffer(), 1));
    }
  else
    return (send_packet_info(client, "ERROR: file no name\n", 1));
  return (0);
}

int		handle_fileinfo(t_client *client, t_packet *packet)
{
  t_file_layer	*file_layer;

  file_layer = (t_file_layer*)packet->data;
  if (file_layer->type == FILELAYER_PUT_BEGIN)
    return (file_put_begin(client, file_layer));
  else if (file_layer->type == FILELAYER_PUT_END)
    {
      if (client->file == NULL)
	return (send_packet_take_prompt(client));
      fclose(client->file);
      client->file = NULL;
      return (send_packet_info(client, "SUCCESS: file been uploaded\n", 1));
    }
  return (0);
}
