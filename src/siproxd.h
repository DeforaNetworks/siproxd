/*
    Copyright (C) 2002  Thomas Ries <tries@gmx.net>

    This file is part of Siproxd.
    
    Siproxd is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    
    Siproxd is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with Siproxd; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
*/



/* sock.c */
int sipsock_listen (void);
int sipsock_wait(void);
int sipsock_read(void *buf, size_t bufsize);
int sipsock_send_udp(struct in_addr addr, int port, char *buffer, int size);

/* register.c */
void register_init(void);
int  register_client(sip_t *request);
void register_agemap(void);
int register_response(sip_t *request, int flag);

/* proxy.c */
int proxy_request (sip_t *request);
int proxy_response (sip_t *response);
int proxy_gen_response(sip_t *request, int code);
int proxy_add_myvia (sip_t *request, int interface);
int proxy_del_myvia (sip_t *response);
int proxy_rewrite_invitation_body(sip_t *mymsg);

/* utils.c */
sip_t * msg_make_template_reply (sip_t * request, int code);
int check_vialoop (sip_t *my_msg);
int is_via_local (via_t *via);
int get_ip_by_host(char *hostname, struct in_addr *addr);

/* config.c */
int read_config(char *name, int search);


/*
 * table to hold the client registrations
 */
struct urlmap_s {
   int  active;
   int  expires;
   url_t *true_url;
   url_t *masq_url;
   via_t *via;
};


/*
 * configuration option table
 */
struct siproxd_config {
   int debuglevel;
   char *inboundhost;
   char *outboundhost;
   int sip_listen_port;
   int daemonize;
};


/*
 * some constant definitions
 */
#define URLMAP_SIZE	128	// size of URL mapping table
#define BUFFER_SIZE	1024	// input buffer for read from socket
#define URL_STRING_SIZE	128	//

#define SIP_PORT	5060

/*
 * optionasl hacks
 */
#define EXP1 1	/* HACK linphone0.9.0pre4 */
/* 14-Aug-2002 TR
   Linphone puts in the proxies hostname in the request URI when
   OUTBOUND proxy is activated. But ONLY the hostname. Username and
   Port (!!!) are kept from the SIP address givven by the user.
   This is a BUG in my eyes. Linphone must send the datagrap to
   the Proxy, but have the final receiver in the request URI !
*/
