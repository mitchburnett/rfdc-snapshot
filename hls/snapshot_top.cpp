#include <iostream>
#include <stdio.h>

#include "snapshot_top.h"

void snapshot_top(hls::stream<axis_t<sample_t> > &I, hls::stream<axis_t<sample_t> > &Q,
                  hls::stream<axis_t<cx_sample_t> > &output,
                  uint16_t length)
{
  #pragma HLS interface axis port=I
  #pragma HLS interface axis port=Q
  #pragma HLS interface axis port=output
  #pragma HLS interface s_axilite port=length bundle=CTRL
  #pragma HLS interface s_axilite port=return bundle=CTRL

  for (uint16_t i=0; i < length; ++i) {
    axis_t<cx_sample_t> tmp;
    axis_t<sample_t> I_tmp = I.read();
    axis_t<sample_t> Q_tmp = Q.read();

    tmp.data.re = I_tmp.data;
    tmp.data.im = Q_tmp.data;
    tmp.last = (i==length-1) ? 1 : 0;

    output.write(tmp);
  }

  return;
}
