/*
** server_create_socket.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:19:08 2014 lamy_a
** Last update Sun Apr 13 21:01:44 2014 lamy_a
*/

#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "server.h"

static struct sockaddr_in	create_name_sock(int port)
{
  struct sockaddr_in		sin;

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  return (sin);
}

static int			prepare_socket(struct sockaddr_in *sin,
					       int port, int *sock)
{
  struct protoent		*protocol;

  *sin = create_name_sock(port);
  protocol = getprotobyname("TCP");
  if (protocol == NULL)
    return (my_error(E_PROTO, 0));
  if ((*sock = socket(PF_INET, SOCK_STREAM, protocol->p_proto)) == -1)
    return (my_error("ftp: ERROR: socket()\n", 1));
  return (0);
}

static void			free_cmd_list(t_cmd_list *list)
{
  t_cmd_list			*tmp;

  while (list != NULL)
    {
      tmp = list;
      list = list->next;
      free(tmp);
    }
}

int				my_ftp(int port, t_handler *ptrf,
				       t_cmd_list *listcmd)
{
  int				sock;
  struct sockaddr_in		sin;
  int				err;
  int				bool;

  bool = 1;
  err = 0;
  if (prepare_socket(&sin, port, &sock))
    return (my_error("ftp: FATAL ERROR", 0));
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &bool, sizeof(bool)) == -1)
    my_error("ftp: ERROR set socket option", 1);
  if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) == 0)
    {
      if (listen(sock, MAX_QUEUE_CONNECT) == 0)
	err = loop_connect(sock, ptrf, listcmd);
      else
	err = my_error("ftp: ERROR listen", 1);
    }
  else
    err = my_error("ftp: ERROR bind", 1);
  close(sock);
  free_cmd_list(listcmd);
  return (err);
}
