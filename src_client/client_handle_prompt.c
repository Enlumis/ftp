/*
** client_handle_prompt.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 18:43:12 2014 lamy_a
** Last update Sun Apr 13 19:19:36 2014 lamy_a
*/

#include <unistd.h>
#include "client.h"

int		handle_prompt(t_client *client, t_packet *packet)
{
  (void)packet;
  client->take_prompt = 1;
  (void)write(1, "vftp $>", 7);
  return (0);
}
