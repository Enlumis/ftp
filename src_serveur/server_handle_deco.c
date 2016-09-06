/*
** server_handle_deco.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:48:44 2014 lamy_a
** Last update Sun Apr 13 21:12:29 2014 lamy_a
*/

#include "server.h"

int	handle_disconnect(t_client *client, t_packet *packet)
{
  (void)packet;
  (void)client;
  return (2);
}
