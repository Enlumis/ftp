/*
** client_add_packet_queue.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 19:00:01 2014 lamy_a
** Last update Sun Apr 13 19:14:59 2014 lamy_a
*/

#include <stdlib.h>
#include "client.h"

int		add_packet_to_queue(t_packet p, t_client *client)
{
  t_packet_list	*packet;

  packet = malloc(sizeof(*packet));
  if (packet == NULL)
    return (my_error("ftp: ERROR: malloc\n", 0));
  packet->packet = p;
  packet->next = NULL;
  if (client->queue == NULL)
    {
      client->queue = packet;
      client->queuetail = packet;
    }
  else
    {
      client->queuetail->next = packet;
      client->queuetail = packet;
    }
  return (0);
}
