/*
  Copyright 2006-2016 Detlef Urban <onkel@paraair.de>

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THIS SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/** Include standard C headers */
#include <math.h>
#include <stdlib.h>
#include "tascam.h"
#include "tascam_vol.h"

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

const LV2_Descriptor descriptor_vol = {
    TASCAM_VOL_URI,
    instantiate_vol,
    connect_port_vol,
    activate_vol,
    run_vol,
    deactivate_vol,
    cleanup_vol,
    extension_data
};

extern LV2_Handle
instantiate_vol(const LV2_Descriptor* descriptor,
        double rate,
        const char* bundle_path,
        const LV2_Feature * const* features) {

    //    fprintf(stdout, "tascam.lv2: instantiate_eq bundle:%s\n", bundle_path);
    Tascam_vol_ports* instance = (Tascam_vol_ports*) calloc(1, sizeof (Tascam_vol_ports));

    if (open_device())
        return NULL;

    return (LV2_Handle) instance;
}

extern void
connect_port_vol(LV2_Handle instance,
        uint32_t port,
        void* data) {
    Tascam_vol_ports* tascam = (Tascam_vol_ports*) instance;

    switch ((PortIndex_vol) port) {
        case TASCAM_VOL_CHANNEL:
            tascam->channel = (const float*) data;
            break;

        case TASCAM_VOL_VOLUME:
            tascam->volume = (const float*) data;
            break;

        case TASCAM_VOL_MUTE:
            tascam->mute = (const float*) data;
            break;

        case TASCAM_VOL_PHASE:
            tascam->phase = (const float*) data;
            break;

        case TASCAM_VOL_PAN:
            tascam->pan = (const float*) data;
            break;

        case TASCAM_VOL_ROUTE:
            tascam->route = (const float*) data;
            break;

        case TASCAM_VOL_INPUT_LEVEL:
            tascam->input_level = (float*) data;
            break;            
    }
}

extern void
activate_vol(LV2_Handle instance) {
//    fprintf(stdout, "tascam_lv2: activate_vol\n");
}

extern void
run_vol(LV2_Handle instance, uint32_t n_samples) {

    const Tascam_vol_ports* tascam = (const Tascam_vol_ports*) instance;

    const int _channel = (int) *(tascam->channel);
    const int _volume = (int) *(tascam->volume);
    const int _mute = (int) *(tascam->mute);
    const int _phase = (int) *(tascam->phase);
    const int _pan = (int) *(tascam->pan);
    const int _route = (int) *(tascam->route);

    float* meter = tascam->input_level;

    if (_channel != -1) {

        *meter = getInputMeterFloat(_channel);
        channel_cache* cache = get_vol_channel_cache(_channel);

        if (_volume != cache->controls[TASCAM_VOL_VOLUME].new_value) {
//            fprintf(stdout, "_volume changed to %d\n", _volume);
            cache->controls[TASCAM_VOL_VOLUME].new_value = _volume;
        }

        if ((_mute != cache->controls[TASCAM_VOL_MUTE].new_value)) {
//            fprintf(stdout, "_mute changed\n");
            cache->controls[TASCAM_VOL_MUTE].new_value = _mute;
        }

        if ((_phase != cache->controls[TASCAM_VOL_PHASE].new_value)) {
//            fprintf(stdout, "_phase changed\n");
            cache->controls[TASCAM_VOL_PHASE].new_value = _phase;
        }

        if ((_pan != cache->controls[TASCAM_VOL_PAN].new_value)) {
//            fprintf(stdout, "_pan changed\n");
            cache->controls[TASCAM_VOL_PAN].new_value = _pan;
        }

        if ((_route != cache->controls[TASCAM_VOL_ROUTE].new_value)) {
//            fprintf(stdout, "_route changed\n");
            cache->controls[TASCAM_VOL_ROUTE].new_value = _route;
        }
    }
}

extern void
deactivate_vol(LV2_Handle instance) {
//    fprintf(stdout, "tascam_lv2: deactivate_vol\n");
}

extern void
cleanup_vol(LV2_Handle instance) {
//    fprintf(stdout, "tascam_lv2: cleanup_vol\n");

    free((Tascam_vol_ports*) instance);
    close_device();
}



