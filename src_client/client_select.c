/*
** client_select.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 18:24:27 2014 lamy_a
** Last update Sun Apr 13 21:19:54 2014 lamy_a
*/

#include <errno.h>
#include <sys/select.h>
#include "client.h"

extern int	g_exit;

static fd_set	prepare_write_set(int sock, fd_set *wfds, t_client *client)
{
  if (client->queue == NULL && client->in_queue == 1)
    {
      client->in_queue = 0;
      FD_CLR(sock, wfds);
    }
  else if (client->queue != NULL && client->in_queue == 0)
    {
      client->in_queue = 1;
      FD_SET(sock, wfds);
    }
  return (*wfds);
}

static void	init_select(int sock, fd_set *read_set, fd_set *write_set)
{
  FD_ZERO(read_set);
  FD_SET(sock, read_set);
  FD_SET(0, read_set);
  FD_ZERO(write_set);
}

static int	do_action_select(t_client *client, t_handler *ptrf,
					 fd_set *read_set, fd_set *write_set)
{
  if (FD_ISSET(client->socket, write_set) &&
      send_packets(client->socket, client))
    return (1);
  if (FD_ISSET(0, read_set) && select_read_command(client))
    return (1);
  if (FD_ISSET(client->socket, read_set))
    return (select_read_server(client, client->socket, ptrf));
  return (0);
}

int		manage_client(t_client *client, int ssock, t_handler *ptrf)
{
  fd_set	rfds;
  fd_set	wfds;
  fd_set	clone_rfds;
  fd_set	clone_wfds;
  int		handle_rep;

  init_select(client->socket, &rfds, &wfds);
  while (!g_exit)
    {
      clone_wfds = prepare_write_set(ssock, &wfds, client);
      clone_rfds = rfds;
      if (select(ssock + 1, &clone_rfds, &clone_wfds, NULL, NULL) == -1)
	{
	  if (errno == EINTR)
	    break ;
	  my_error("ftp: ERROR select", 1);
	}
      handle_rep = do_action_select(client, ptrf, &clone_rfds, &clone_wfds);
      if (handle_rep == 1)
	return (1);
      if (handle_rep == 2)
	break ;
    }
  return (0);
}
