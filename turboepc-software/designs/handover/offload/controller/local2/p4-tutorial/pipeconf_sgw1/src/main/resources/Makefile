all: epc

epc: epc_handover_offload_1chain_sgw1.p4
	p4c-bm2-ss -o mytunnel.json --p4runtime-file mytunnel.p4info --p4runtime-format text epc_handover_offload_1chain_sgw1.p4
