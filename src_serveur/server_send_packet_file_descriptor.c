/*
** server_send_packet_file_descriptor.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:28:36 2014 lamy_a
** Last update Sun Apr 13 20:28:53 2014 lamy_a
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "server.h"

int		send_packet_file_descriptor(t_client *client, char *filename,
					    mode_t mode, char begin)
{
  t_packet	packet;
  t_file_layer	*layer;

  client->nb_packet_sent_for_file = 0;
  packet.packet_id = PACKET_FILEINFO;
  packet.data_len = PACKET_DATA_SIZE;
  bzero(packet.data, PACKET_DATA_SIZE);
  layer = (t_file_layer*)packet.data;
  if (begin)
    {
      layer->mode = mode;
      layer->type = FILELAYER_GET_BEGIN;
    }
  else
    layer->type = FILELAYER_GET_END;
  strcpy(layer->file_name, filename);
  if (begin)
    printf("send file [%s]\n", layer->file_name);
  if (add_packet_to_queue(packet, client))
    return (my_error("ftp: ERROR: send packet info\n", 0));
  return (0);
}
