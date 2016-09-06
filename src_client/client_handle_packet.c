/*
** client_handle_packet.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 19:06:25 2014 lamy_a
** Last update Sun Apr 13 19:18:35 2014 lamy_a
*/

#include "client.h"

int	handle_packet(t_client *client, t_packet *packet, t_handler *ptrf)
{
  if (packet->packet_id >= NBR_PACKET)
    return (my_error(E_UNKNOWN, packet->packet_id));
  return (ptrf[packet->packet_id](client, packet));
}
