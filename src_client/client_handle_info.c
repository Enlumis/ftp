/*
** client_handle_info.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 18:41:26 2014 lamy_a
** Last update Sun Apr 13 19:28:55 2014 lamy_a
*/

#include <string.h>
#include <unistd.h>
#include "client.h"

int	handle_info(t_client *client, t_packet *packet)
{
  (void)client;
  (void)write(1, (char*)packet->data, strlen((char*)packet->data));
  return (0);
}
