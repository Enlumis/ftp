/*
** client_handle_deco.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 18:42:20 2014 lamy_a
** Last update Sun Apr 13 19:16:57 2014 lamy_a
*/

#include "client.h"

int		handle_deco(t_client *client, t_packet *packet)
{
  if (add_packet_to_queue(*packet, client))
    return (1);
  return (2);
}
