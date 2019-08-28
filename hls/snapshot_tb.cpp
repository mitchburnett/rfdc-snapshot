#include <iostream>
#include <string>
#include <stdio.h>

#include "snapshot_top.h"

#define TRANSFERS 3

int main () {

  std::cout << "\nRFDC Snapshot Capture Testbench\n";

  hls::stream<axis_t<cx_sample_t> > output_strm("snapshot_strm");
  hls::stream<axis_t<sample_t> > I_strm("RFDC_I_strm");
  hls::stream<axis_t<sample_t> > Q_strm("RFDC_Q_strm");

  uint16_t transfer_size_array[TRANSFERS] = {8, 4, 16};

  for (uint16_t j=0; j < TRANSFERS; j++) {
    uint16_t transfer_size = transfer_size_array[j];
    std::cout << "Starting next transfer...\n";
    std::cout<< "Transferring " << transfer_size << " samples\n";

    for (uint16_t i=0; i < transfer_size; ++i) {
      axis_t<sample_t> I_sample;
      axis_t<sample_t> Q_sample;

      I_sample.data = i;
      Q_sample.data = i;

      I_strm.write(I_sample);
      Q_strm.write(Q_sample);
    }

    snapshot_top(I_strm, Q_strm, output_strm, transfer_size);

    for (uint16_t i=0; i < transfer_size; ++i) {
      axis_t<cx_sample_t> axis_out = output_strm.read();

      std::cout << "{re: " << axis_out.data.re;
      std::cout << ", im: " << axis_out.data.im;
      std::cout << ", last: " << axis_out.last;
      std::cout << "}" << std::endl;

    }
  }

  return 0;
}
