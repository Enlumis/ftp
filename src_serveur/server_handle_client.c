/*
** server_handle_client.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:46:05 2014 lamy_a
** Last update Sun Apr 13 21:16:22 2014 lamy_a
*/

#include <unistd.h>
#include "server.h"

static int		handle_packet(t_client *client, t_packet *packet,
				      t_handler *ptrf)
{
  if (packet->packet_id >= NBR_PACKET)
    return (my_error(E_UNKNOWN, packet->packet_id));
  return (ptrf[packet->packet_id](client, packet));
}

int			handle_client(t_client *cl, t_handler *ptrf)
{
  int			rd;
  int			handle_errno;

  if (cl->try_read_again)
    {
      rd = read(cl->socket, cl->buffer + cl->rd, sizeof(t_packet) - cl->rd);
      cl->rd += rd;
    }
  else
    cl->rd = read(cl->socket, cl->buffer, sizeof(t_packet));
  if (cl->rd <= 0)
    return (my_error("ftp: ERROR: read error client\n", 0));
  if (cl->rd != sizeof(t_packet))
    {
      cl->try_read_again = 1;
      return (0);
    }
  cl->rd = 0;
  cl->try_read_again = 0;
  handle_errno = handle_packet(cl, (t_packet*)cl->buffer, ptrf);
  if (handle_errno == 1)
    return (my_error("ftp: ERROR: packet process error\n", 0));
  if (handle_errno == 2)
    return (1);
  return (0);
}
