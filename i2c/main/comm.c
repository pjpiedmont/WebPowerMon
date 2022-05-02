#include "comm.h"
#include "INA209.h"
#include "esp_log.h"

/**
 * @brief i2c master initialization
 */
esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

void readINA(void *pvParameters)
{
	int v = 0;
	int i = 0;
	int p = 0;

	const char *TAG = "readINA";

	while (1)
	{
		v = busVol();
		ESP_LOGI(TAG, "Bus voltage = %d mV", v);

		i = current();
		ESP_LOGI(TAG, "Current = %d uA", i*100);

		p = power();
		ESP_LOGI(TAG, "Power = %d mW", p*2);

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}