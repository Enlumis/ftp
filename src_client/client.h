/*
** client.h for client in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Wed Apr  9 16:12:22 2014 lamy_a
** Last update Sun Apr 13 21:20:08 2014 lamy_a
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <stdio.h>
# include <sys/types.h>
# include "../packet.h"

# define E_PORT "ftp: ERROR: the port can be between 0 and 65535 inclusive"
# define E_PROTO "ftp: ERROR: the protocol TCP doesn't exist (/etc/protocols)"
# define E_UNKNOWN "ftp: ERROR: packet %d unknown\n"

typedef struct	s_client
{
  char		buffer[sizeof(t_packet)];
  int		rd;
  int		try_read_again;
  int		socket;
  int		server_socket;
  int		take_prompt;
  FILE		*file;
  t_packet_list	*queue;
  t_packet_list	*queuetail;
  char		in_queue;
  char		file_name[PACKET_DATA_SIZE];
}		t_client;

typedef	int (*t_handler)(t_client*, t_packet*);

int	add_packet_to_queue(t_packet p, t_client *client);
int	my_ftp(char *host, int port);
int	my_error(char *format, int perrno, ...);
int	handle_deco(t_client *client, t_packet *packet);
int	handle_default(t_client *client, t_packet *packet);
int	handle_filepart(t_client *client, t_packet *p);
int	handle_fileinfo(t_client *client, t_packet *packet);
int	handle_info(t_client *client, t_packet *packet);
int	handle_packet(t_client *client, t_packet *packet, t_handler *ptrf);
int	handle_prompt(t_client *client, t_packet *packet);
int	send_packet_file_descriptor(t_client *client, char *filename,
				    mode_t mode, char begin);
int	manage_client(t_client *client, int ssock, t_handler *ptrf);
int	select_read_command(t_client *client);
int	select_read_server(t_client *cl, int ssock, t_handler *ptr);
int	send_packets(int socket, t_client *client);
void	exit_client(int sig);
int	my_usage(char *prog_name);

#endif /* !CLIENT_H_ */
