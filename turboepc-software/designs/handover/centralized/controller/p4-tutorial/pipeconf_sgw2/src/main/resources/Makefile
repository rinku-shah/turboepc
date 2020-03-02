all: epc

epc: epc_handover_centralized_1chain_sgw2.p4
	p4c-bm2-ss -o mytunnel.json --p4runtime-file mytunnel.p4info --p4runtime-format text epc_handover_centralized_1chain_sgw2.p4
