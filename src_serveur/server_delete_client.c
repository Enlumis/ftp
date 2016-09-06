/*
** server_delete_client.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:41:02 2014 lamy_a
** Last update Sun Apr 13 21:02:17 2014 lamy_a
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

static void		free_packetqueue(t_client *client)
{
  t_packet_list		*packet;
  t_packet_list		*lastpacket;

  packet = client->packetlist;
  while (packet != NULL)
    {
      lastpacket = packet;
      packet = packet->next;
      free(lastpacket);
    }
}

t_client		*delete_client(t_client *client, t_client **list)
{
  t_client		*tmp;
  t_client		*last;

  tmp = client->next;
  printf(CLIENT_DISCONNECT, inet_ntoa(client->addr.sin_addr));
  if (client == *list)
    *list = tmp;
  else
    {
      last = *list;
      while (last != NULL && last->next != NULL && last->next != client)
	last = last->next;
      last->next = tmp;
    }
  if (client->file != NULL)
    fclose(client->file);
  free_packetqueue(client);
  close(client->socket);
  free(client);
  return (tmp);
}
