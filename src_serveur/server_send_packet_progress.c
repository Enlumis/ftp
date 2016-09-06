/*
** server_send_packet_progress.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:27:19 2014 lamy_a
** Last update Sun Apr 13 20:29:17 2014 lamy_a
*/

#include <string.h>
#include "server.h"

int		send_packet_file_progress(t_client *client)
{
  t_packet	packet;
  char		bufferprintf[1024];
  double	percent;
  long		max_packet;

  bzero(packet.data, PACKET_DATA_SIZE);
  packet.packet_id = PACKET_INFO;
  packet.data_len = PACKET_DATA_SIZE;
  max_packet = client->file_size / PACKET_DATA_SIZE;
  percent = ((double)client->nb_packet_sent_for_file / max_packet) * 100;
  snprintf(bufferprintf, 1024, "%.2f Mo / %.2f Mo [%.2f%%]      ",
	   client->nb_packet_sent_for_file / 244.14f,
	   client->file_size / PACKET_DATA_SIZE / 244.14f,
	   percent);
  strcat((char*)packet.data, "\r");
  strcat((char*)packet.data, bufferprintf);
  if (add_packet_to_queue(packet, client))
    return (my_error("ftp: ERROR: send file progress info\n", 0));
  return (0);
}
