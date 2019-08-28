#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "ap_int.h"
#include "hls_stream.h"
#include "stdint.h" // for uint16_t, couldn't seem to override with ap_uint<16>

typedef ap_int<16> sample_t;

struct cx_sample_t {
	sample_t re;
	sample_t im;
};

template<typename T>
struct axis_t {
  T data;
  ap_uint<1> last;
  
};

#endif // TYPEDEFS_H
