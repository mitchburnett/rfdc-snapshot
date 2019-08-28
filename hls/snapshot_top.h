#ifndef SNAPSHOT_TOP_H
#define SNAPSHOT_TOP_H

#include "typedefs.h"

void snapshot_top(hls::stream<axis_t<sample_t> > &I,
                  hls::stream<axis_t<sample_t> > &Q,
                  hls::stream<axis_t<cx_sample_t> > &output,
                  uint16_t length);

#endif // SNAPSHOT_TOP_H
