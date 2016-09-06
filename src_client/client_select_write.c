/*
** client_select_write.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 18:46:57 2014 lamy_a
** Last update Sun Apr 13 19:30:09 2014 lamy_a
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "client.h"

static int	handle_send_file(t_client *client)
{
  t_packet	packet;
  unsigned char	buffer[PACKET_DATA_SIZE];
  int		rd;

  if (client->file == NULL)
    return (my_error("ERROR: No file can be sent\n", 0));
  if ((rd = fread(buffer, sizeof(char), PACKET_DATA_SIZE, client->file)) == -1)
    return (my_error("ERROR: read file on server\n", 0));
  if (rd == PACKET_DATA_SIZE || rd != 0)
    {
      packet.packet_id = PACKET_FILEPART;
      packet.data_len = rd;
      memcpy(packet.data, buffer, rd);
      if (add_packet_to_queue(packet, client))
	return (my_error("ERROR: send file packet\n", 0));
    }
  else if (rd == 0)
    {
      fclose(client->file);
      client->file = NULL;
      if (send_packet_file_descriptor(client, "", 0, 0))
	return (my_error("ERROR: send end of file\n", 0));
      return (0);
    }
  return (0);
}

int		send_packets(int socket, t_client *client)
{
  t_packet_list	*tmp;
  t_packet	*packet;
  t_file_layer	*filelayer;

  if (client->queue != NULL)
    {
      packet = &client->queue->packet;
      filelayer = (t_file_layer*)packet->data;
      if (write(socket, packet, sizeof(t_packet)) != sizeof(t_packet))
	return (my_error("ftp: ERROR: write client socket\n", 0));
      tmp = client->queue;
      client->queue = client->queue->next;
      if (client->queue == NULL)
	client->queuetail = NULL;
      if (packet->packet_id == PACKET_FILEPART ||
	  (packet->packet_id == PACKET_FILEINFO &&
	   filelayer->type == FILELAYER_PUT_BEGIN))
	if (handle_send_file(client))
	  {
	    free(tmp);
	    return (my_error("ERROR: send file\n", 0));
	  }
      free(tmp);
    }
  return (0);
}
