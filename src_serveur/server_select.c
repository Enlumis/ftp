/*
** server_select.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:33:18 2014 lamy_a
** Last update Sun Apr 13 21:14:17 2014 lamy_a
*/

#include <errno.h>
#include <sys/select.h>
#include <stdio.h>
#include "server.h"

extern int	g_exit;

static void	init_server(t_server *server, int ssock, t_cmd_list *cmd_list)
{
  server->clientlist = NULL;
  server->socket = ssock;
  server->cmdlist = cmd_list;
  FD_ZERO(&server->write_set);
  FD_ZERO(&server->read_set);
  FD_SET(ssock, &server->read_set);
  server->sockmax = ssock;
}

static fd_set	prepate_write_set(t_server *server)
{
  t_client	*tmp;

  tmp = server->clientlist;
  while (tmp != NULL)
    {
      if (tmp->packetlist != NULL)
	{
	  if (tmp->in_queue == 0)
	    FD_SET(tmp->socket, &server->write_set);
	  tmp->in_queue = 1;
	}
      else if (tmp->packetlist == NULL && tmp->in_queue)
	{
	  tmp->in_queue = 0;
	  FD_CLR(tmp->socket, &server->write_set);
	}
      tmp = tmp->next;
    }
  return (server->write_set);
}

static void	do_select_clients(t_server *server, t_handler *ptrf,
				  fd_set cp_read, fd_set cp_write)
{
  t_client	*tmp;

  if (FD_ISSET(server->socket, &cp_read))
    accept_new_client(server);
  tmp = server->clientlist;
  while (tmp != NULL)
    {
      if (FD_ISSET(tmp->socket, &cp_write) &&
	  send_packets(tmp))
	{
	  FD_CLR(tmp->socket, &server->write_set);
	  FD_CLR(tmp->socket, &server->read_set);
	  tmp = delete_client(tmp, &server->clientlist);
	}
      else if (FD_ISSET(tmp->socket, &cp_read) &&
	       (handle_client(tmp, ptrf) || tmp->exit))
	{
	  if (tmp->in_queue)
	    FD_CLR(tmp->socket, &server->write_set);
	  FD_CLR(tmp->socket, &server->read_set);
	  tmp = delete_client(tmp, &server->clientlist);
	}
      else
	tmp = tmp->next;
    }
}

int		loop_connect(int ssock, t_handler *ptrf, t_cmd_list *cmdlist)
{
  fd_set	cp_write;
  fd_set	cp_read;
  t_server	server;

  init_server(&server, ssock, cmdlist);
  while (!g_exit)
    {
      cp_read = server.read_set;
      cp_write = prepate_write_set(&server);
      if (select(server.sockmax + 1, &cp_read, &cp_write, NULL, NULL) == -1)
	{
	  if (errno == EINTR)
	    break ;
	  my_error("ftp: ERROR select", 1);
	}
      do_select_clients(&server, ptrf, cp_read, cp_write);
    }
  printf("\b\b%s", STOP_SERVER);
  return (0);
}
