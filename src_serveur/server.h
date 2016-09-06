/*
** server.h for packet in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Wed Apr  9 16:06:23 2014 lamy_a
** Last update Sun Apr 13 21:11:48 2014 lamy_a
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <dirent.h>
# include <netinet/in.h>
# include <stdint.h>
# include <sys/types.h>
# include <stdio.h>
# include "../packet.h"

# define NB_BETWEEN_PINFO 1000
# define MAX_QUEUE_CONNECT 8

# define E_PORT "ftp: ERROR: the port can be between 0 and 65535 inclusive\n"
# define E_PROTO "ftp: ERROR: the protocol doesn't exist (/etc/protocols)\n"
# define E_ACCEPT "ftp: ERROR: accept()"
# define E_UNKNOWN "ftp: ERROR: packet %d unknown, bad client.\n"

# define START_SERVER	"|---------------/ START SERVER \\----------------|\n"
# define PORT_SERVER	"|                  port: %-5d                  |\n"
# define STOP_SERVER	"|---------------\\ STOP  SERVER /----------------|\n"

# define CLIENT_DISCONNECT "Client: %s diconnected\n"
# define CLIENT_CONNECT "Client: %s connected\n"

typedef struct s_cmd_list	t_cmd_list;
typedef struct s_client		t_client;

typedef	int (*t_cmd_handler)(t_client*, int, char**);
typedef	int (*t_handler)(t_client*, t_packet*);

struct				s_cmd_list
{
  struct s_cmd_list		*next;
  const char			*name;
  t_cmd_handler			cmd;
};

struct				s_client
{
  int				socket;
  char				buffer[sizeof(t_packet)];
  char				try_read_again;
  int				rd;
  t_cmd_list			*cmd_list;
  t_packet_list			*packetlist;
  t_packet_list			*packetlisttail;
  char				in_queue;
  FILE				*file;
  char				exit;
  off_t				file_size;
  int				next_packet_info;
  long				nb_packet_sent_for_file;
  struct sockaddr_in		addr;
  char				path[PATH_MAX];
  char				root_path[PATH_MAX];
  int				hide_path;
  struct s_client		*next;
};

typedef struct			s_server
{
  fd_set			read_set;
  fd_set			write_set;
  t_client			*clientlist;
  t_cmd_list			*cmdlist;
  int				sockmax;
  int				socket;
}				t_server;

int		handle_cmd(t_client *client, t_packet *packet);
char		*get_perror_buffer();
int		my_error(char *format, int perrno, ...);
char		*get_filename(char *path);
char		*get_format_file(char *path, struct dirent *file);
int		cmd_ls(t_client *client, int ac, char **av);
int		cmd_cd(t_client *client, int ac, char **av);
int		cmd_help(t_client *client, int ac, char **av);
int		cmd_pwd(t_client *client, int ac, char **av);
int		cmd_quit(t_client *client, int ac, char **av);
int		cmd_get(t_client *client, int ac, char **av);
int		cmd_put(t_client *client, int ac, char **av);
int		accept_new_client(t_server *server);
void		init_cmd_list(t_cmd_list **list);
int		my_usage(char *prog_name);
int		add_packet_to_queue(t_packet p, t_client *client);
void		exit_sock(int sig);
int		my_ftp(int port, t_handler *ptrf, t_cmd_list *listcmd);
int		send_packet_take_prompt(t_client *client);
int		send_packet_info(t_client *client, char *data, int takeprompt);
int		send_packet_file_descriptor(t_client *client, char *filename,
					    mode_t mode, char begin);
int		send_packet_file_progress(t_client *client);
int		loop_connect(int ssock, t_handler *ptrf, t_cmd_list *cmdlist);
t_client	*delete_client(t_client *client, t_client **list);
int		send_packets(t_client *client);
int		handle_client(t_client *cl, t_handler *ptrf);
int		handle_disconnect(t_client *client, t_packet *packet);
int		handle_default(t_client *client, t_packet *packet);
int		handle_fileinfo(t_client *client, t_packet *packet);
int		handle_filepart(t_client *client, t_packet *p);

#endif /* !SERVER_H_ */
