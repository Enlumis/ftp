/*
** client_create_socket.c for cilent in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 18:50:17 2014 lamy_a
** Last update Sun Apr 13 21:20:16 2014 lamy_a
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include "client.h"

static int		create_name_sock(struct sockaddr_in *sin,
					 char *hoststr, int port)
{
  struct hostent	*host;

  host = gethostbyname(hoststr);
  if (host == NULL)
    return (1);
  sin->sin_addr = *(struct in_addr*)host->h_addr_list[0];
  sin->sin_family = AF_INET;
  sin->sin_port = htons(port);
  printf("Connexion to %s, port %d\n", host->h_name, port);
  return (0);
}

static void		init_handler(t_handler *ptrf)
{
  ptrf[PACKET_CMD] = handle_default;
  ptrf[PACKET_DECO] = handle_deco;
  ptrf[PACKET_INFO] = handle_info;
  ptrf[PACKET_PROMPT] = handle_prompt;
  ptrf[PACKET_FILEPART] = handle_filepart;
  ptrf[PACKET_FILEINFO] = handle_fileinfo;
}

static void		init_client(t_client *client, int socket)
{
  client->take_prompt = 0;
  client->file = NULL;
  client->queue = NULL;
  client->queuetail = NULL;
  client->in_queue = 0;
  client->socket = socket;
  client->rd = 0;
  client->try_read_again = 0;
}

int			my_ftp(char *host, int port)
{
  int			sock;
  struct sockaddr_in	sin;
  struct protoent	*protocol;
  t_handler		ptrf[NBR_PACKET];
  t_client		client;

  init_handler(ptrf);
  protocol = getprotobyname("TCP");
  if (protocol == NULL)
    return (my_error("%s\n", 0, E_PROTO));
  if (create_name_sock(&sin, host, port))
    return (my_error("ftp: socket_init ERROR", 0));
  if ((sock = socket(PF_INET, SOCK_STREAM, protocol->p_proto)) == -1)
    return (my_error("ftp: socket ERROR", 1));
  if (connect(sock, (const struct sockaddr*)&sin, sizeof(sin)) != -1)
    {
      init_client(&client, sock);
      manage_client(&client, sock, ptrf);
    }
  else
    my_error("ftp: connect ERROR", 1);
  close(sock);
  return (0);
}
