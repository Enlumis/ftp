/*
** server_handle_filepart.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:52:45 2014 lamy_a
** Last update Sun Apr 13 20:52:56 2014 lamy_a
*/

#include <stdio.h>
#include "server.h"

int	handle_filepart(t_client *client, t_packet *p)
{
  if (client->file != NULL)
    {
      if (fwrite(p->data, sizeof(char), p->data_len, client->file) <= 0)
	return (my_error("Error: write file\n", 0));
    }
  return (0);
}
