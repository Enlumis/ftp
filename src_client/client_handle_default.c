/*
** client_handle_default.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 18:40:42 2014 lamy_a
** Last update Sun Apr 13 19:17:16 2014 lamy_a
*/

#include "client.h"

int		handle_default(t_client *client, t_packet *packet)
{
  my_error("ftp: ERROR: packet[%d] uncatched\n", 0, packet->packet_id);
  (void)client;
  (void)packet;
  return (0);
}
