all: epc

epc: epc_4chainparallel_sgw3.p4
	p4c-bm2-ss -o mytunnel.json --p4runtime-file mytunnel.p4info --p4runtime-format text epc_4chainparallel_sgw3.p4
