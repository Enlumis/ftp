/*
** server_exit.c for server in /home/lamy_a/rendu/PSU_2013_myftp/src_serveur
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 20:15:25 2014 lamy_a
** Last update Sun Apr 13 20:22:40 2014 lamy_a
*/

int	g_exit = 0;

void	exit_sock(int sig)
{
  (void)sig;
  g_exit = 1;
}
