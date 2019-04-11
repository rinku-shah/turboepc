all: epc_basic

epc_basic: epc_basic_offload_pgw.p4
	p4c-bm2-ss -o mytunnel.json --p4runtime-file mytunnel.p4info --p4runtime-format text epc_basic_offload_pgw.p4
