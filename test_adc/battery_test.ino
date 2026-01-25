/*
 * Battery ADC Test for nice!nano v2
 * Reads both VBAT pin AND internal VDDHDIV5 (what ZMK uses)
 */

#include <nrfx_saadc.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);  // Wait for USB serial

  analogReference(AR_INTERNAL_3_0);  // 3.0V reference
  analogReadResolution(12);           // 12-bit resolution

  Serial.println("\n=== Battery ADC Test for nice!nano v2 ===");
  Serial.println("Comparing VBAT pin vs VDDHDIV5 (ZMK method)");
  Serial.println("Reading every 2 seconds...\n");
}

// Read internal VDDHDIV5 - exactly what ZMK does
int readVDDHDIV5() {
  int16_t value;

  nrf_saadc_channel_config_t config = {
    .resistor_p = NRF_SAADC_RESISTOR_DISABLED,
    .resistor_n = NRF_SAADC_RESISTOR_DISABLED,
    .gain = NRF_SAADC_GAIN1_2,
    .reference = NRF_SAADC_REFERENCE_INTERNAL,
    .acq_time = NRF_SAADC_ACQTIME_40US,
    .mode = NRF_SAADC_MODE_SINGLE_ENDED,
    .burst = NRF_SAADC_BURST_DISABLED,
    .pin_p = NRF_SAADC_INPUT_VDDHDIV5,  // Internal VDDH/5
    .pin_n = NRF_SAADC_INPUT_DISABLED
  };

  nrf_saadc_resolution_set(NRF_SAADC, NRF_SAADC_RESOLUTION_12BIT);
  nrf_saadc_oversample_set(NRF_SAADC, NRF_SAADC_OVERSAMPLE_4X);
  nrf_saadc_channel_init(NRF_SAADC, 0, &config);
  nrf_saadc_enable(NRF_SAADC);

  nrf_saadc_buffer_init(NRF_SAADC, &value, 1);
  nrf_saadc_task_trigger(NRF_SAADC, NRF_SAADC_TASK_START);
  while (!nrf_saadc_event_check(NRF_SAADC, NRF_SAADC_EVENT_STARTED));
  nrf_saadc_event_clear(NRF_SAADC, NRF_SAADC_EVENT_STARTED);

  nrf_saadc_task_trigger(NRF_SAADC, NRF_SAADC_TASK_SAMPLE);
  while (!nrf_saadc_event_check(NRF_SAADC, NRF_SAADC_EVENT_END));
  nrf_saadc_event_clear(NRF_SAADC, NRF_SAADC_EVENT_END);

  nrf_saadc_task_trigger(NRF_SAADC, NRF_SAADC_TASK_STOP);
  while (!nrf_saadc_event_check(NRF_SAADC, NRF_SAADC_EVENT_STOPPED));
  nrf_saadc_event_clear(NRF_SAADC, NRF_SAADC_EVENT_STOPPED);

  nrf_saadc_disable(NRF_SAADC);

  return value;
}

int calcPercent(int mv) {
  if (mv >= 4200) return 100;
  if (mv <= 3450) return 0;
  return (mv - 3450) * 100 / (4200 - 3450);
}

void loop() {
  // Method 1: VDDHDIV5 (what ZMK uses)
  int vddh_raw = readVDDHDIV5();
  // Convert: raw * (0.6V ref / gain 0.5) / 4096 * 5 (divider) * 1000
  int vddh_mv = (int)(vddh_raw * 0.6 / 0.5 / 4096.0 * 5.0 * 1000.0);
  int vddh_pct = calcPercent(vddh_mv);

  // Method 2: VBAT analog pin (if connected)
  int vbat_raw = analogRead(A6);
  int vbat_mv = (int)(vbat_raw * 3.0 / 4096.0 * 2.0 * 1000.0);
  int vbat_pct = calcPercent(vbat_mv);

  Serial.println("----------------------------------------");
  Serial.print("VDDHDIV5 (ZMK): raw=");
  Serial.print(vddh_raw);
  Serial.print(" | ");
  Serial.print(vddh_mv);
  Serial.print("mV | ");
  Serial.print(vddh_pct);
  Serial.println("%");

  Serial.print("VBAT pin:       raw=");
  Serial.print(vbat_raw);
  Serial.print(" | ");
  Serial.print(vbat_mv);
  Serial.print("mV | ");
  Serial.print(vbat_pct);
  Serial.println("%");

  delay(2000);
}
