/*
** server_send_packet_prompt.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:24:32 2014 lamy_a
** Last update Sun Apr 13 20:24:57 2014 lamy_a
*/

#include "server.h"

int		send_packet_take_prompt(t_client *client)
{
  t_packet	p;

  p.packet_id = PACKET_PROMPT;
  p.data_len = PACKET_DATA_SIZE;
  if (add_packet_to_queue(p, client))
    return (1);
  return (0);
}
