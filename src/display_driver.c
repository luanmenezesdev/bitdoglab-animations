#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "include/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"

#define I2C_PORT i2c0
#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15

const int VRX = 26;          
const int VRY = 27;         
const int ADC_CHANNEL_0 = 0;
const int ADC_CHANNEL_1 = 1; 
const int SW = 22; 

uint8_t ssd[ssd1306_buffer_length];
struct render_area frame_area;

void init_oled() {
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    ssd1306_init();

    
    frame_area.start_column = 0;
    frame_area.end_column = ssd1306_width - 1;
    frame_area.start_page = 0;
    frame_area.end_page = ssd1306_n_pages - 1;

    calculate_render_area_buffer_length(&frame_area);

    
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);
}

void display_message(char *line1, char *line2, char *line3) {
    // Limpa o buffer 
    memset(ssd, 0, ssd1306_buffer_length);

    // Desenha as strings
    ssd1306_draw_string(ssd, 5, 0, line1);
    if (line2 != NULL) {
        ssd1306_draw_string(ssd, 5, 8, line2);
    }
    if (line3 != NULL) {
        ssd1306_draw_string(ssd, 5, 16, line3); 
    }

    render_on_display(ssd, &frame_area);
}

void menu(int selected_option){
    memset(ssd, 0, ssd1306_buffer_length);

    // Mostra as opções com destaque para a selecionada
    ssd1306_draw_string(ssd, 5, 0, (selected_option == 0) ? "o clock" : "  clock");
    ssd1306_draw_string(ssd, 5, 8, (selected_option == 1) ? "o embarcatech" : "  embarcatech");
    ssd1306_draw_string(ssd, 5, 16, (selected_option == 2) ? "o heart" : "  heart");

    render_on_display(ssd, &frame_area);
}

void setup_joystick(){
  
  adc_init();         
  adc_gpio_init(VRX); 
  adc_gpio_init(VRY); 

  
  gpio_init(SW);             
  gpio_set_dir(SW, GPIO_IN);
  gpio_pull_up(SW); 
}    

int read_joystick_vertical() {
    adc_select_input(ADC_CHANNEL_1);
    uint16_t value = adc_read();
    //printf("ADC Value (VRY): %d\n", value);
    if (value > 2350) return -1; // Mover para cima
    if (value < 1950) return 1;  // Mover para baixo
    return 0; // Neutro
}

bool read_joystick_button() {
    return !gpio_get(SW); // Retorna verdadeiro se o botão estiver pressionado
}

