/*
** server_accept_client.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:06:23 2014 lamy_a
** Last update Sun Apr 13 21:12:02 2014 lamy_a
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "server.h"

static void		init_client(t_client *client)
{
  client->file = NULL;
  client->packetlist = NULL;
  client->packetlisttail = NULL;
  client->in_queue = 0;
  client->try_read_again = 0;
  client->rd = 0;
  client->next = NULL;
  client->next_packet_info = 0;
  client->exit = 0;
}

static int		add_client(t_client **list, int csock,
				   struct sockaddr_in addr, t_cmd_list *cmds)
{
  t_client		*newclient;

  newclient = malloc(sizeof(*newclient));
  if (newclient == NULL)
    return (my_error("ftp: ERROR: malloc new client\n", 0));
  newclient->socket = csock;
  if (getcwd(newclient->path, PATH_MAX) == NULL)
    return (my_error("ftp: ERROR", 1));
  strcat(newclient->path, "/");
  strcpy(newclient->root_path, newclient->path);
  newclient->cmd_list = cmds;
  newclient->addr = addr;
  init_client(newclient);
  newclient->hide_path = strlen(newclient->root_path) - 1;
  printf(CLIENT_CONNECT, inet_ntoa(addr.sin_addr));
  if (*list != NULL)
    newclient->next = *list;
  *list = newclient;
  if (send_packet_take_prompt(newclient))
    return (my_error("ftp: ERROR: prompt fatal error\n", 0));
  return (0);
}

int			accept_new_client(t_server *server)
{
  int			csock;
  struct sockaddr_in	caddr;
  socklen_t		clen;

  clen = sizeof(caddr);
  if ((csock = accept(server->socket, (struct sockaddr*)&caddr, &clen)) != -1)
    {
      if (!add_client(&server->clientlist, csock, caddr, server->cmdlist))
	{
	  FD_SET(csock, &server->read_set);
	  if (csock > server->sockmax)
	    server->sockmax = csock;
	}
    }
  else
    my_error("ftp: ERROR accept", 1);
  return (0);
}
