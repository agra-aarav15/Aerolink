/* VPN stub — All VPN calls are no-ops. */
#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"

extern int32_t  vpn_enabled;
extern bool     vpn_connected;
extern uint32_t vpn_tunnel_ip;
extern int32_t  vpn_port;
extern int32_t  vpn_keepalive;
extern char    *vpn_private_key;
extern char    *vpn_public_key;
extern char    *vpn_preshared_key;
extern char    *vpn_endpoint;
extern char    *vpn_address;
extern char    *vpn_netmask;
extern char    *vpn_dns;
extern int32_t  vpn_killswitch;
extern int32_t  vpn_route_all;

static inline esp_err_t vpn_connect(void)             { return ESP_OK; }
static inline void      vpn_disconnect(void)           {}
static inline bool      vpn_is_connected(void)         { return false; }
static inline void      vpn_reassert_default_route(void) {}
static inline void      vpn_connect_task(void *pv)     { (void)pv; }
static inline void      vpn_set_subnet(uint32_t i, uint32_t m) { (void)i; (void)m; }
static inline bool      vpn_in_subnet(uint32_t i)      { (void)i; return false; }
