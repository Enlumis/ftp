/*
** client_signal_exit.c for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 13 19:02:34 2014 lamy_a
** Last update Sun Apr 13 19:32:55 2014 lamy_a
*/

int	g_exit = 0;

void	exit_client(int sig)
{
  (void)sig;
  g_exit = 1;
}
