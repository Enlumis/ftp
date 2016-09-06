/*
** client_error.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 18:36:41 2014 lamy_a
** Last update Sun Apr 13 19:28:00 2014 lamy_a
*/

#include <stdio.h>
#include <errno.h>
#include <stdarg.h>

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
