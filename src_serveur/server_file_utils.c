/*
** server_file_utils.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 19:52:02 2014 lamy_a
** Last update Sun Apr 13 21:05:01 2014 lamy_a
*/

#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include "packet.h"

char		*get_filename(char *path)
{
  int		i;

  i = strlen(path) - 1;
  while (i >= 0)
    {
      if (path[i] == '/')
	return (path + i + 1);
      --i;
    }
  return (path);
}

char		*get_format_file(char *path, struct dirent *file)
{
  static char	buffersnd[MAXPATHLEN * 2];
  char		abspath[MAXPATHLEN * 2];
  struct stat	stats;

  bzero(abspath, MAXPATHLEN * 2);
  bzero(buffersnd, MAXPATHLEN * 2);
  strcat(abspath, path);
  strcat(abspath, "/");
  strcat(abspath, file->d_name);
  if (lstat(abspath, &stats) >= 0 && (stats.st_mode & S_IFMT) == S_IFDIR)
    strcat(buffersnd, "[Dir]  ");
  else
    strcat(buffersnd, "[File] ");
  strcat(buffersnd, file->d_name);
  strcat(buffersnd, "\n");
  if (strlen(buffersnd) >= PACKET_DATA_SIZE)
    {
      buffersnd[0] = '\0';
      strcat(buffersnd, "File name is too long\n");
    }
  return (buffersnd);
}
