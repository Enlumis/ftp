/*
** server_send_packet.c for server$ in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:44:39 2014 lamy_a
** Last update Sun Apr 13 20:44:43 2014 lamy_a
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

static int		progress_send_file(t_client *client)
{
  if (client->next_packet_info > NB_BETWEEN_PINFO)
    {
      if (send_packet_file_progress(client))
	return (my_error("ERROR: send packet progress\n", 0));
      client->next_packet_info = 0;
    }
  client->next_packet_info++;
  client->nb_packet_sent_for_file++;
  return (0);
}

static int		handle_send_file(t_client *client)
{
  t_packet		packet;
  unsigned char		buffer[PACKET_DATA_SIZE];
  int			rd;

  if (client->file == NULL)
    return (my_error("ERROR: No file can be sent\n", 0));
  if (progress_send_file(client))
    return (1);
  if ((rd = fread(buffer, sizeof(char), PACKET_DATA_SIZE, client->file)) == -1)
    return (my_error("ERROR: read file on server\n", 0));
  if (rd == PACKET_DATA_SIZE || rd != 0)
    {
      packet.packet_id = PACKET_FILEPART;
      packet.data_len = rd;
      memcpy(packet.data, buffer, rd);
      if (add_packet_to_queue(packet, client))
	return (my_error("ERROR: send file packet\n", 0));
      return (0);
    }
  fclose(client->file);
  client->file = NULL;
  if (send_packet_file_descriptor(client, "", 0, 0))
    return (my_error("ERROR: send end of file\n", 0));
  return (send_packet_info(client, "SUCCESS: file has been receive\n", 1));
}

int			send_packets(t_client *client)
{
  t_packet_list		*tmp;
  t_packet		*packet;
  t_file_layer		*filelayer;

  if (client->packetlist != NULL)
    {
      packet = &client->packetlist->packet;
      filelayer = (t_file_layer*)packet->data;
      if (write(client->socket, packet, sizeof(t_packet)) != sizeof(t_packet))
	return (my_error("ftp: ERROR: write client socket\n", 0));
      tmp = client->packetlist;
      client->packetlist = client->packetlist->next;
      if (client->packetlist == NULL)
	client->packetlisttail = NULL;
      if (packet->packet_id == PACKET_FILEPART ||
	  (packet->packet_id == PACKET_FILEINFO &&
	   filelayer->type == FILELAYER_GET_BEGIN))
	if (handle_send_file(client))
	  {
	    free(tmp);
	    return (my_error("ERROR: send file\n", 0));
	  }
      free(tmp);
    }
  return (0);
}
