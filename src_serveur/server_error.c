/*
** server_error.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 19:49:00 2014 lamy_a
** Last update Sun Apr 13 19:50:15 2014 lamy_a
*/

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include "packet.h"

char		*get_perror_buffer()
{
  static char	buffer[PACKET_DATA_SIZE];
  char		*strerro;

  strerro = strerror(errno);
  bzero(buffer, PACKET_DATA_SIZE);
  strcat(buffer, "ERROR: ");
  if (strlen(buffer) + strlen(strerro) > PACKET_DATA_SIZE - 2)
    {
      strcat(buffer, "Unknown error\n");
      return (buffer);
    }
  strcat(buffer, strerro);
  strcat(buffer, "\n");
  return (buffer);
}

int		my_error(char *format, int perrno, ...)
{
  va_list	list;

  if (perrno)
    {
      perror(format);
      return (1);
    }
  va_start(list, perrno);
  vfprintf(stderr, format, list);
  va_end(list);
  return (1);
}
