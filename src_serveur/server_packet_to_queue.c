/*
** server_packet_to_queue.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:12:52 2014 lamy_a
** Last update Sun Apr 13 20:13:17 2014 lamy_a
*/

#include <stdlib.h>
#include "server.h"

int		add_packet_to_queue(t_packet p, t_client *client)
{
  t_packet_list	*packet;

  packet = malloc(sizeof(*packet));
  if (packet == NULL)
    return (my_error("ftp: ERROR: malloc\n", 0));
  packet->packet = p;
  packet->next = NULL;
  if (client->packetlist == NULL)
    {
      client->packetlist = packet;
      client->packetlisttail = packet;
    }
  else
    {
      client->packetlisttail->next = packet;
      client->packetlisttail = packet;
    }
  return (0);
}
