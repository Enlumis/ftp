/*
** client_packet_file_descriptor.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 19:05:35 2014 lamy_a
** Last update Sun Apr 13 19:19:55 2014 lamy_a
*/

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include "client.h"

int		send_packet_file_descriptor(t_client *client, char *filename,
					    mode_t mode, char begin)
{
  t_file_layer	*layer;
  t_packet	packet;

  packet.packet_id = PACKET_FILEINFO;
  packet.data_len = PACKET_DATA_SIZE;
  bzero(packet.data, PACKET_DATA_SIZE);
  layer = (t_file_layer*)packet.data;
  if (begin)
    {
      layer->mode = mode;
      layer->type = FILELAYER_PUT_BEGIN;
    }
  else
    layer->type = FILELAYER_PUT_END;
  strcpy(layer->file_name, filename);
  if (begin)
    printf("Send file [%s]\n", layer->file_name);
  if (add_packet_to_queue(packet, client))
    return (my_error("ftp: ERROR: send packet info\n", 0));
  return (0);
}
