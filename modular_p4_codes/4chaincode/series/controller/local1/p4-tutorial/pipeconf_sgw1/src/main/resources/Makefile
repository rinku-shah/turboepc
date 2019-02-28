all: epc_sgw1

epc_sgw1: epc_4chainseries_sgw1.p4
	p4c-bm2-ss -o mytunnel.json --p4runtime-file mytunnel.p4info --p4runtime-format text epc_4chainseries_sgw1.p4
