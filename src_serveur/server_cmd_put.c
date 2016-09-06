/*
** server_cmd_put.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:37:53 2014 lamy_a
** Last update Sun Apr 13 20:38:04 2014 lamy_a
*/

#include <string.h>
#include "server.h"

int		cmd_put(t_client *client, int ac, char **av)
{
  t_packet	packet;
  t_file_layer	*file_layer;

  if (ac != 2)
    return (send_packet_info(client, "Usage: put filename\n", 1));
  packet.packet_id = PACKET_FILEINFO;
  packet.data_len = PACKET_DATA_SIZE;
  bzero(packet.data, PACKET_DATA_SIZE);
  file_layer = (t_file_layer*)packet.data;
  file_layer->type = FILELAYER_PUT_ISEXIST;
  if (strlen(av[1]) >= sizeof(file_layer->file_name))
    return (send_packet_info(client, "ERROR: filename is too long\n", 1));
  strcpy(file_layer->file_name, av[1]);
  if (add_packet_to_queue(packet, client))
    return (my_error("ERROR: init file insertion\n", 0));
  return (0);
}
