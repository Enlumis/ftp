/*
** server_cmd_quit.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 19:55:31 2014 lamy_a
** Last update Sun Apr 13 21:12:38 2014 lamy_a
*/

#include "server.h"

int		cmd_quit(t_client *client, int ac, char **av)
{
  t_packet	packet;

  (void)ac;
  (void)av;
  client->exit = 1;
  packet.packet_id = PACKET_DECO;
  packet.data_len = PACKET_DATA_SIZE;
  if (add_packet_to_queue(packet, client))
    return (my_error("ftp: ERROR: send packet deco\n", 0));
  return (0);
}
