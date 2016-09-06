/*
** server_cmd_help.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 19:53:21 2014 lamy_a
** Last update Sun Apr 13 21:01:01 2014 lamy_a
*/

#include <string.h>
#include "server.h"

int		cmd_help(t_client *client, int ac, char **av)
{
  char		hbuf[PACKET_DATA_SIZE];

  (void)ac;
  (void)av;
  bzero(hbuf, PACKET_DATA_SIZE);
  strcat(hbuf, "  *  Server VFTP (Very Fast Tranfert Protocol)  *\n\n");
  strcat(hbuf, "Commands:\n");
  strcat(hbuf, "ls <path>\tList contents of current folder or 'path'\n");
  strcat(hbuf, "cd <path>\tGo to directory 'path'\n");
  strcat(hbuf, "pwd\t\tSee the path of current folder\n");
  strcat(hbuf, "put <file>\tPut a local 'file' to the server\n");
  strcat(hbuf, "get <file>\tDownload 'file' on the server\n");
  strcat(hbuf, "quit\t\tExit and close connexion\n");
  if (send_packet_info(client, hbuf, 1))
    return (1);
  return (0);
}
