# RFDC Snapshot Demo

## Introduction
This project is a minimal example for how to setup and interface with the ADC 
the RFDC on the ZCU111 using PYNQ. The ADC samples are sent via DMA from the PL
to the PS for analysis.

## Project structure and files
This project is built using Vivado Design Suite 2018.3 with Vivado HLS.

The `hls` directory contains an implementation of an snapshot block for
generating the tlast signal required to packetize data over the DMA using AXIS.

The `py` directory contains the relevant jupyter notebook to run the project.

The `vivado` directory contains the project tcl script generating the Vivado
project and starting implementation through to writing the bitstream. This
directory also contains the completed bitstream and hwh file to immedatiely copy
to PYNQ and program the ZCU111. here is also where the HLS project generates and
stores custom snapshot IP for use in the Vivado project.

## Project and ZCU111 Setup
Since the bitstream and hwh file are already included in this repository under
`vivado/overlay` they can be copied directly to the ZCU111 and programmed using
the jupyter notebook under `py`. For instructions on building the HLS IP and
Vivado project from scratch see [building from scratch below](#building-the-project).

For this project ADC0 on tile 224 is used for the input signal. Using the balun
board provided with the ZCU111 evaluation kit this corresponds to designator J5.
The RFDC ADC is configured with a sampling rate of 2048 MHz, fine mixer mode
producing I/Q samples, and using a decimation rate of 8. The NCO frequency is
set in the jupyter notebook to 512 MHz (fs/4) making this our basebanded
frequency center. The total bandwidth is 128 MHz spanning from 448 to 640 MHz.
Therefore injecting any tone within this range will appear in the resulting
output spectrum.

Modify the path in the jupyter notebook to point to the provided overlay and
begin executing the notebook cells. Note that digitization does not begin until
the LMX PLL clock has been programmed.

## Building the Project
The top-level makefile will kick off the entire build process by first
generating the Vivado HLS project and exporting the IP to be used in the Vivado
project.

To build the project
```
cd /path/to/rfdc-snapshot
source <XILINX_PATH>/Vivado/2018.3/settings64.sh
make
```
This will run through the entire build in batch mode (as opposed to gui).
Afterwards the `hls` directory will contain a `hls/snapshot_prj` directory that
can be opened in Vivado HLS. Likewise the `vivado` directory will contain a
`vivado/rfdc_snapshot_prj` containing a project that can be opened with Vivado
Design Suite.
