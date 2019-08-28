# Makefile

snapshot_dir := hls
vivado_dir := vivado

all: snapshot_prj vivado_prj

snapshot_prj:
	cd $(snapshot_dir); vivado_hls -f run_hls.tcl
	mkdir -p $(vivado_dir)/ip/vivado
	cp -r $(snapshot_dir)/$@/sol1/impl $(vivado)/ip/vivado

vivado_prj:
	cd vivado; vivado -source write_prj.tcl
