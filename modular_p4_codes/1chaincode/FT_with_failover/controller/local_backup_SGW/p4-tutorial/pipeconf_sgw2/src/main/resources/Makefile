all: epc_ft

epc_ft: epc_1chain_ft_with_failover_backupsgw.p4
	p4c-bm2-ss -o mytunnel.json --p4runtime-file mytunnel.p4info --p4runtime-format text epc_1chain_ft_with_failover_backupsgw.p4
