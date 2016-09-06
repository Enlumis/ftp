##
## Makefile for myftp in /home/lamy_a/rendu/PSU_2013_myftp
## 
## Made by lamy_a
## Login   <lamy_a@epitech.net>
## 
## Started on  Sun Apr 13 01:12:20 2014 lamy_a
## Last update Sun Apr 13 21:06:18 2014 lamy_a
##

CC		= gcc

RM		= rm -f

CFLAGS		= -W -Werror -Wall -pedantic -I.

NAMECLIENT	= client

SRCCLIENT	= src_client/main.c \
		  src_client/client_create_socket.c \
		  src_client/client_add_packet_queue.c \
		  src_client/client_error.c \
		  src_client/client_handle_deco.c \
		  src_client/client_handle_default.c \
		  src_client/client_handle_fileinfo.c \
		  src_client/client_handle_filepart.c \
		  src_client/client_handle_info.c \
		  src_client/client_handle_packet.c \
		  src_client/client_handle_prompt.c \
		  src_client/client_packet_file_descriptor.c \
		  src_client/client_select.c \
		  src_client/client_select_read.c \
		  src_client/client_select_write.c \
		  src_client/client_signal_exit.c \
		  src_client/client_usage.c

OBJCLIENT	= $(SRCCLIENT:.c=.o)

NAMESERVER	= serveur

SRCSERVER	= src_serveur/main.c \
		  src_serveur/server_accept_client.c \
		  src_serveur/server_cmd_cd.c \
		  src_serveur/server_cmd_get.c \
		  src_serveur/server_cmd_help.c \
		  src_serveur/server_cmd_ls.c \
		  src_serveur/server_cmd_put.c \
		  src_serveur/server_cmd_pwd.c \
		  src_serveur/server_cmd_quit.c \
		  src_serveur/server_create_socket.c \
		  src_serveur/server_delete_client.c \
		  src_serveur/server_error.c \
		  src_serveur/server_exit.c \
		  src_serveur/server_file_utils.c \
		  src_serveur/server_handle_client.c \
		  src_serveur/server_handle_cmd.c \
		  src_serveur/server_handle_deco.c \
		  src_serveur/server_handle_default.c \
		  src_serveur/server_handle_fileinfo.c \
		  src_serveur/server_handle_filepart.c \
		  src_serveur/server_init_cmd.c \
		  src_serveur/server_packet_to_queue.c \
		  src_serveur/server_select.c \
		  src_serveur/server_send_packet.c \
		  src_serveur/server_send_packet_file_descriptor.c \
		  src_serveur/server_send_packet_info.c \
		  src_serveur/server_send_packet_progress.c \
		  src_serveur/server_send_packet_prompt.c \
		  src_serveur/server_usage.c

OBJSERVER	= $(SRCSERVER:.c=.o)

all: $(NAMECLIENT) $(NAMESERVER)

$(NAMECLIENT): $(OBJCLIENT)
	$(CC) $(OBJCLIENT) -o $(NAMECLIENT)

$(NAMESERVER): $(OBJSERVER)
	$(CC) $(OBJSERVER) -o $(NAMESERVER)

clean:
	$(RM) $(OBJCLIENT)
	$(RM) $(OBJSERVER)

fclean: clean
	$(RM) $(NAMECLIENT)
	$(RM) $(NAMESERVER)

re: fclean all

.PHONY: all clean fclean re