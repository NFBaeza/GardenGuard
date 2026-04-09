#pragma once

// ── lwIP options for GardenGuard (Pico 2 W, NO_SYS poll mode) ───────────────

#define NO_SYS                      1
#define LWIP_SOCKET                 0
#define LWIP_NETCONN                0

// ── Memory ───────────────────────────────────────────────────────────────────
// MEM_SIZE must be large enough to hold TCP send/receive buffers.
// With TCP_MSS=536, TCP_SND_BUF=2*536=1072, TCP_WND=2*536=1072 → ~4 KB active;
// 16 KB gives plenty of headroom for DHCP, ARP, and MQTT payload pbufs.
#define MEM_LIBC_MALLOC             0
#define MEMP_MEM_MALLOC             0
#define MEM_ALIGNMENT               4
#define MEM_SIZE                    16000

// ── Pbuf pool ────────────────────────────────────────────────────────────────
#define PBUF_POOL_SIZE              24
#define MEMP_NUM_PBUF               16
#define MEMP_NUM_TCP_SEG            16
#define MEMP_NUM_ARP_QUEUE          10
#define MEMP_NUM_SYS_TIMEOUT        16

// ── TCP ───────────────────────────────────────────────────────────────────────
// Smaller MSS (536) keeps buffer requirements low on constrained WiFi links.
#define LWIP_TCP                    1
#define TCP_TTL                     255
#define TCP_MSS                     536
#define TCP_SND_BUF                 (2 * TCP_MSS)
#define TCP_SND_QUEUELEN            ((4 * (TCP_SND_BUF) + (TCP_MSS - 1)) / (TCP_MSS))
#define TCP_WND                     (2 * TCP_MSS)
#define LWIP_TCP_KEEPALIVE          1

// ── DHCP / ARP / ICMP ────────────────────────────────────────────────────────
#define LWIP_DHCP                   1
#define LWIP_ARP                    1
#define LWIP_ICMP                   1
#define LWIP_RAW                    1
#define LWIP_ETHERNET               1
#define LWIP_NETIF_STATUS_CALLBACK  1
#define LWIP_NETIF_LINK_CALLBACK    1
#define LWIP_NETIF_HOSTNAME         1
#define DHCP_DOES_ARP_CHECK         0
#define LWIP_DHCP_DOES_ACD_CHECK    0

// ── DNS ───────────────────────────────────────────────────────────────────────
#define LWIP_DNS                    1
#define LWIP_UDP                    1

// ── MQTT / altcp ─────────────────────────────────────────────────────────────
#define LWIP_ALTCP                  1
#define MQTT_OUTPUT_RINGBUF_SIZE    512
#define MQTT_VAR_HEADER_BUFFER_LEN  256

// ── Stats / debug (off for release) ──────────────────────────────────────────
#define LWIP_STATS                  0
#define MEM_STATS                   0
#define MEMP_STATS                  0
#define SYS_STATS                   0
#define LINK_STATS                  0
#define LWIP_DEBUG                  0