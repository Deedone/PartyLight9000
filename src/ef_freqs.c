#include "ef_freqs.h"

#include "sound.h"
#include "ws8212.h"
#define HALFLEDS (NUMLED/2)

float h = 0;
float log[HALFLEDS] = {0};
int smooth[HALFLEDS] = {0};
uint16_t indexmap[SAMPLES];

void build_index(int samples) {
    float maxlog = log2f(samples/2);
    int prevlogind = -1;
    for(int i = 2; i < samples/2; i++) {
        //+5 to filter topmost freqs
        int logind = (log2f(i) / maxlog) * (HALFLEDS + 4);
        if  (abs(logind - prevlogind) > 1) {
            logind = prevlogind + 1;
        }
        prevlogind = logind;
        if (logind >=HALFLEDS && logind != -1) {
            logind = HALFLEDS - 1;
        }
        indexmap[i] = logind;
    }
}
void freqs_process(float smoothing, int samples, float speed) {
    capture(samples);
    //GPIOA->ODR |= 1 << 7;
    process(samples);
    //GPIOA->ODR &= ~(1 << 7);
    ws8212_update();
    float noise = 20000;
    h+= speed;
    if (h > 360) h = 0;

    memset(log, 0, sizeof(log));
    for(int i = 0; i < samples/2; i++) {
        if (fft_input[i] > log[indexmap[i]]) {
            log[indexmap[i]] = fft_input[i];
        }
    }

    for(int i = 0; i < HALFLEDS; i++) {
      if (log[i] < noise)
      log[i] = 0;
      int val = (log[i] / 100000) * 100;
      if (val > 100) val = 100;
      if (val < 0) val = 0;
      smooth[i] = val* (1.0 - smoothing) + smooth[i] * smoothing;

      ws8212_setHSV(HALFLEDS+i, ((int)h+i*2)%360, 100,  smooth[i]);
      ws8212_setHSV(HALFLEDS-1-i, ((int)h+i*2)%360, 100,  smooth[i]);
    }


}