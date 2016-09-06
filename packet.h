/*
** packet.h for packet in /home/lamy_a/rendu/PSU_2013_myftp
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Wed Apr  9 00:31:20 2014 lamy_a
** Last update Sun Apr 13 21:03:38 2014 lamy_a
*/

#ifndef PACKET_H_
# define PACKET_H_

# include <linux/limits.h>
# include <stdint.h>
# include <sys/stat.h>
# include <unistd.h>

# define PACKET_DATA_SIZE	4096

# define NBR_PACKET		6
# define PACKET_CMD		0
# define PACKET_DECO		1
# define PACKET_INFO		2
# define PACKET_PROMPT		3
# define PACKET_FILEINFO	4
# define PACKET_FILEPART	5

# define FILELAYER_GET_BEGIN	0
# define FILELAYER_GET_PROGRESS	1
# define FILELAYER_GET_END	2

# define FILELAYER_PUT_ISEXIST	10
# define FILELAYER_PUT_BEGIN	11
# define FILELAYER_PUT_PROGRESS	12
# define FILELAYER_PUT_END	13

typedef struct			s_packet
{
  uint16_t			packet_id;
  uint16_t			data_len;
  unsigned char			data[PACKET_DATA_SIZE];
}__attribute__((__packed__))	t_packet;

typedef struct			s_file_layer
{
  char				type;
  mode_t			mode;
  char				file_name[PACKET_DATA_SIZE - 32];
}				t_file_layer;

typedef struct			s_packet_list
{
  t_packet			packet;
  struct s_packet_list		*next;
}				t_packet_list;

#endif /* !PACKET_H_ */
