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

#ifndef TASCAM_VOL_H
#define TASCAM_VOL_H

#include <math.h>
#include <stdlib.h>
#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

#include "tascam_alsa.h"

#define TASCAM_VOL_URI "http://www.paraair.de/plugins/tascam_vol"

typedef enum {
    TASCAM_VOL_VOLUME,
    TASCAM_VOL_MUTE,
    TASCAM_VOL_PHASE,
    TASCAM_VOL_PAN,
    TASCAM_VOL_ROUTE,
    TASCAM_VOL_CHANNEL,
    TASCAM_VOL_INPUT_LEVEL,
} PortIndex_vol;


typedef struct {
	// Port buffers
	const float* channel;
        const float* volume; 
        const float* mute;
        const float* phase;
        const float* pan;
        const float* route;
        float* input_level;
	const float* input;
	float*       output;
} Tascam_vol_ports;

extern LV2_Handle
instantiate_vol(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features);

extern void
connect_port_vol(LV2_Handle instance,
             uint32_t   port,
             void*      data);

extern void
activate_vol(LV2_Handle instance);

extern void
run_vol(LV2_Handle instance, uint32_t n_samples);

extern void
deactivate_vol(LV2_Handle instance);

extern void
cleanup_vol(LV2_Handle instance);

extern const LV2_Descriptor descriptor_vol;

#endif // TASCAM_VOL_H
