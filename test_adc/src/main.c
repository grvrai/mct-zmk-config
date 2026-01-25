/*
 * Minimal battery ADC test for nice!nano v2
 * Reads VDDHDIV5 and logs the raw value and millivolts
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(battery_test, LOG_LEVEL_INF);

#define VDDHDIV (5)

static const struct device *adc_dev = DEVICE_DT_GET(DT_NODELABEL(adc));

static int16_t adc_raw;
static struct adc_channel_cfg channel_cfg = {
    .gain = ADC_GAIN_1_2,
    .reference = ADC_REF_INTERNAL,
    .acquisition_time = ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 40),
    .input_positive = SAADC_CH_PSELN_PSELN_VDDHDIV5,
};

static struct adc_sequence sequence = {
    .channels = BIT(0),
    .buffer = &adc_raw,
    .buffer_size = sizeof(adc_raw),
    .oversampling = 4,
    .calibrate = true,
    .resolution = 12,
};

/* Convert millivolts to percentage (same formula as ZMK) */
static uint8_t mv_to_pct(int32_t mv) {
    if (mv >= 4200) return 100;
    if (mv <= 3450) return 0;
    return (mv - 3450) * 100 / (4200 - 3450);
}

int main(void) {
    int ret;

    printk("\n\n=== Battery ADC Test for nice!nano v2 ===\n");
    printk("This reads VDDHDIV5 directly and logs the result.\n\n");

    if (!device_is_ready(adc_dev)) {
        printk("ERROR: ADC device not ready!\n");
        return -1;
    }

    ret = adc_channel_setup(adc_dev, &channel_cfg);
    if (ret < 0) {
        printk("ERROR: ADC channel setup failed: %d\n", ret);
        return ret;
    }

    printk("ADC initialized. Reading battery every 2 seconds...\n\n");

    while (1) {
        ret = adc_read(adc_dev, &sequence);
        sequence.calibrate = false;  /* Only calibrate first time */

        if (ret < 0) {
            printk("ERROR: ADC read failed: %d\n", ret);
        } else {
            int32_t mv = adc_raw;

            /* Convert raw to millivolts */
            adc_raw_to_millivolts(adc_ref_internal(adc_dev),
                                  channel_cfg.gain,
                                  sequence.resolution,
                                  &mv);

            /* Multiply by 5 because we're reading VDDHDIV5 */
            mv = mv * VDDHDIV;

            uint8_t pct = mv_to_pct(mv);

            printk("ADC raw: %d | Voltage: %d mV | Battery: %d%%\n",
                   adc_raw, mv, pct);

            LOG_INF("ADC raw: %d | Voltage: %d mV | Battery: %d%%",
                    adc_raw, mv, pct);
        }

        k_sleep(K_SECONDS(2));
    }

    return 0;
}
