# Create a project
open_project -reset snapshot_prj

# The source file and test bench
add_files snapshot_top.cpp
add_files -tb snapshot_tb.cpp

# Specify the top-level function for synthesis
set_top snapshot_top

# Create solution1
open_solution -reset sol1

# Specify a Xilinx device and clock period
set_part  {xczu28dr-ffvg1517-2-e}
create_clock -period 10

# Simulate the C code 
csim_design

# Syntesize, Verify the RTL and produce IP (for sysgen add `-format sysgen`)
csynth_design
cosim_design 
export_design
exit