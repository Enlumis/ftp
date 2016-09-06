/*
** server_send_packet_info.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:25:52 2014 lamy_a
** Last update Sun Apr 13 20:25:56 2014 lamy_a
*/

#include <string.h>
#include "server.h"

int		send_packet_info(t_client *client, char *data, int takeprompt)
{
  t_packet	packet;

  packet.packet_id = PACKET_INFO;
  packet.data_len = PACKET_DATA_SIZE;
  strncpy((char*)packet.data, data, PACKET_DATA_SIZE);
  if (add_packet_to_queue(packet, client))
    return (my_error("ftp: ERROR: send packet info\n", 0));
  if (takeprompt)
    if (send_packet_take_prompt(client))
      return (1);
  return (0);
}
