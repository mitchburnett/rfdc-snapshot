#include <iostream>
#include <stdio.h>

#include "snapshot_top.h"

void merge(hls::stream<axis_t<sample_t> > &I, hls::stream<axis_t<sample_t> > &Q,
                  hls::stream<axis_t<cx_sample_t> > &output,
                  uint16_t length)

{
  for (uint16_t i=0; i < 16; ++i) {
  #pragma HLS pipeline II=1 rewind
  axis_t<cx_sample_t> tmp;
  axis_t<sample_t> I_tmp = I.read();
  axis_t<sample_t> Q_tmp = Q.read();

  tmp.data.re = I_tmp.data;
  tmp.data.im = Q_tmp.data;
  tmp.last = (i==length-1) ? 1 : 0;
  output.write(tmp);
  }

}

void snapshot_top(hls::stream<axis_t<sample_t> > &I, hls::stream<axis_t<sample_t> > &Q,
                  hls::stream<axis_t<cx_sample_t> > &output,
                  uint16_t length)
{
  #pragma HLS interface axis port=I
  #pragma HLS interface axis port=Q
  #pragma HLS interface axis port=output
//  #pragma HLS interface s_axilite port=length bundle=CTRL
//  #pragma HLS interface ap_ctrl_chain port=return
  #pragma HLS interface s_axilite port=return bundle=CTRL
//#pragma HLS interface ap_ctrl_none port=return
#pragma HLS pipeline II=16
//#pragma HLS dataflow
//    merge(I, Q, output, length);

    for (uint16_t i=0; i < 16; ++i) {
//    for (uint16_t i=0; i < length; ++i) {
//    #pragma HLS pipeline II=1// rewind
//  #pragma HLS latency max=1
//  #pragma HLS dataflow
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
