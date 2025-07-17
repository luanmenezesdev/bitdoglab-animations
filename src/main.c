#include <stdio.h>
#include "pico/stdlib.h"
#include "led_animation.h"
#include "np_driver.h"
#include "clock_animations.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/dns.h"
#include "lwip/init.h"
#include <string.h>

#define LED_PIN 7

#define HOST "worldtimeapi.org"
#define PATH "/api/timezone/America/Sao_Paulo"
#define PORT 80

#define WIFI_SSID "Redmi Note 12"
#define WIFI_PASS "luanteste"

struct tcp_pcb *tcp_client_pcb;
static char request[256];

volatile int atualizado = 0;

// Atualiza os ponteiros do relógio com hora, minuto e segundo
void iniciar_animacao_com_tempo(int hora, int minuto, int segundo)
{
    uint64_t now = to_ms_since_boot(get_absolute_time());

    float hora_float = (hora % 12) + (minuto / 60.0f) + (segundo / 3600.0f);
    float minuto_float = minuto + (segundo / 60.0f);

    printf("Iniciando animação: %02d:%02d:%02d (Hora: %.2f, Minuto: %.2f)\n", hora, minuto, segundo, hora_float, minuto_float);

    animation_start_at(&seconds_hand, now, segundo, 60.0f);
    animation_start_at(&minutes_hand, now, minuto_float, 60.0f);
    animation_start_at(&hours_hand, now, hora_float, 12.0f);
}

static err_t tcp_recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    if (p == NULL)
    {
        tcp_close(tpcb);
        return ERR_OK;
    }

    char *payload = (char *)p->payload;
    int len = p->len;

    printf("Resposta: %.*s\n", len, payload);

    // Busca o campo "datetime"
    char *datetime_ptr = strstr(payload, "\"datetime\":\"");
    if (datetime_ptr)
    {
        datetime_ptr += strlen("\"datetime\":\"");

        int hora, minuto, segundo;
        if (sscanf(datetime_ptr + 11, "%2d:%2d:%2d", &hora, &minuto, &segundo) == 3)
        {
            printf("Hora atual: %02d:%02d:%02d\n", hora, minuto, segundo);
            iniciar_animacao_com_tempo(hora, minuto, segundo);
            atualizado = 1;
        }
        else
        {
            printf("Erro ao interpretar hora.\n");
        }
    }
    else
    {
        printf("Campo datetime não encontrado.\n");
    }

    pbuf_free(p);
    tcp_close(tpcb);
    return ERR_OK;
}

static err_t tcp_connect_callback(void *arg, struct tcp_pcb *tpcb, err_t err)
{
    if (err != ERR_OK)
    {
        printf("Falha ao conectar ao servidor.\n");
        return err;
    }

    printf("Conectado ao servidor.\n");

    snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Connection: close\r\n\r\n",
             PATH, HOST);

    err_t write_err = tcp_write(tpcb, request, strlen(request), TCP_WRITE_FLAG_COPY);
    if (write_err != ERR_OK)
    {
        printf("Erro ao enviar requisição: %d\n", write_err);
        tcp_close(tpcb);
        return write_err;
    }

    tcp_output(tpcb);
    tcp_recv(tpcb, tcp_recv_callback);

    return ERR_OK;
}

static void dns_callback(const char *name, const ip_addr_t *ipaddr, void *callback_arg)
{
    if (ipaddr == NULL)
    {
        printf("Falha ao resolver DNS para %s\n", name);
        return;
    }

    printf("Resolvido %s para %s\n", name, ipaddr_ntoa(ipaddr));

    if (tcp_client_pcb == NULL)
    {
        tcp_client_pcb = tcp_new();
        if (!tcp_client_pcb)
        {
            printf("Falha ao criar TCP PCB.\n");
            return;
        }
    }

    err_t err = tcp_connect(tcp_client_pcb, ipaddr, PORT, tcp_connect_callback);
    if (err != ERR_OK)
    {
        printf("Erro ao conectar: %d\n", err);
        tcp_close(tcp_client_pcb);
        tcp_client_pcb = NULL;
    }
}

// Inicia o processo de sincronização do relógio via HTTP
void sincronizar_relogio_com_internet()
{
    tcp_client_pcb = tcp_new();
    if (!tcp_client_pcb)
    {
        printf("Falha ao criar TCP PCB.\n");
        return;
    }

    ip_addr_t server_ip;
    err_t err = dns_gethostbyname(HOST, &server_ip, dns_callback, NULL);
    if (err == ERR_OK)
    {
        printf("DNS já resolvido.\n");
        tcp_connect(tcp_client_pcb, &server_ip, PORT, tcp_connect_callback);
    }
    else if (err == ERR_INPROGRESS)
    {
        printf("Resolução de DNS em andamento...\n");
    }
    else
    {
        printf("Erro ao iniciar resolução DNS: %d\n", err);
    }
}

int main()
{
    stdio_init_all();
    sleep_ms(2000); // tempo para terminal iniciar

    if (cyw43_arch_init())
    {
        printf("Erro ao inicializar WiFi\n");
        return -1;
    }

    cyw43_arch_enable_sta_mode();

    // Conecte-se à sua rede WiFi aqui:
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 10000))
    {
        printf("Erro ao conectar ao WiFi\n");
        return -1;
    }

    printf("WiFi conectado!\n");

    npInit(LED_PIN);

    while (!atualizado)
    {
        printf("Sincronizando relógio com a internet...\n");
        sincronizar_relogio_com_internet();
        sleep_ms(2000);
    }

    while (true)
    {
        uint64_t now = to_ms_since_boot(get_absolute_time());

        npClear();
        animation_render(&hours_hand, now);
        animation_render(&minutes_hand, now);
        animation_render(&seconds_hand, now);
        npWrite();

        sleep_ms(16);
    }

    return 0;
}
