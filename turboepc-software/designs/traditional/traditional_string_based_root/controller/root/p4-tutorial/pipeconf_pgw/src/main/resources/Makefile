all: mytunnel

mytunnel: epc_centralized_string_pgw.p4
	p4c-bm2-ss -o mytunnel.json --p4runtime-file mytunnel.p4info --p4runtime-format text epc_centralized_string_pgw.p4
