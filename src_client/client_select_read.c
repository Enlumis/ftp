/*
** client_select_read.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 18:46:11 2014 lamy_a
** Last update Sun Apr 13 19:30:00 2014 lamy_a
*/

#include <string.h>
#include <unistd.h>
#include "client.h"

static void	prepare_cmd(t_packet *packet, char *buf, int rd)
{
  packet->packet_id = PACKET_CMD;
  packet->data_len = rd;
  bzero(packet->data, PACKET_DATA_SIZE);
  strncpy((char*)packet->data, buf, rd);
}

int		select_read_command(t_client *client)
{
  char		buffer[sizeof(t_packet)];
  int		rd;
  t_packet	packet;

  if ((rd = read(0, buffer, PACKET_DATA_SIZE)) > 0)
    {
      if (buffer[0] != '\n' && client->take_prompt)
	{
	  client->take_prompt = 0;
	  prepare_cmd(&packet, buffer, rd - 1);
	  if (add_packet_to_queue(packet, client))
	    return (my_error("\nftp: ERROR: server unreachable\n", 0));
	}
      else if (client->take_prompt)
	(void)write(1, "vftp $>", 7);
    }
  return (0);
}

int		select_read_server(t_client *cl, int ssock, t_handler *ptr)
{
  int		rd;

  if (cl->try_read_again)
    {
      rd = read(ssock, cl->buffer + cl->rd, sizeof(t_packet) - cl->rd);
      cl->rd += rd;
    }
  else
    cl->rd = read(ssock, cl->buffer, sizeof(t_packet));
  if (cl->rd <= 0)
    return (my_error("\nftp: ERROR: server unreachable\n", 0));
  if (cl->rd != sizeof(t_packet))
    {
      cl->try_read_again = 1;
      return (0);
    }
  cl->rd = 0;
  cl->try_read_again = 0;
  return (handle_packet(cl, (t_packet*)cl->buffer, ptr));
}
