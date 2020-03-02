# TurboEPC
Accelerate mobile core network control plane functions using programmable switches

## Publication
Rinku Shah, Vikas Kumar, Mythili Vutukuru, Purushottam Kulkarni. "TurboEPC: Leveraging Dataplane Programmability to Accelerate the Mobile Packet Core". In the ACM SIGCOMM Symposium on SDN Research (SOSR), 2020

## Designs:

traditional- All control plane messages serviced by Root controller, only GTP processing at switches.

basic- All offloadable messages (service request/context release/GTP processing) processed at the switch, and attach/detach at the Root controller. We consider that the user state is always available at the switch (always HIT).

parallel- Single chain (one edge switch) with the user context is partitioned among 3 edge switches in parallel.

series- Single chain (one edge switch) with the user context is partitioned among 3 edge switches in series.

FT- Single chain of RAN-DGW-SGW-PGW-SINK with SGW-FT instance where the UE state is mirrored so that under failures the user state at the failed switch is not lost. 

handover- In this setup the user registers, establishes session with chain 2, handover is done over chain 1, delete the tunnel created over chain 2. case 6 in ran.cpp is used for this scenario. The load geneator configuration for only handovers is, service_request and s1_release flags are kept false. loop 1 and loop 2 values are set to be 1.

## Roadmap

Installation steps :
Please follow steps from turboepc/turboepc-hardware/smartnic-setup-steps for hardware Netronome setup and turboepc/turboepc-software/installation_steps.txt for software bmv2 setup

# FAQs
## ONOS : 
    a. after too many runs, if the onos does not behave as expected please do the following
    1. cd onos
    2. rm -rf buck-out 
    3. again start onos as usual using run_onos.sh script 
    b. To check flows using ONOS  
    1. open onos cli using `onos localhost'
    2. cli> flows -s
    3. For more help on cli goto https://wiki.onosproject.org/display/ONOS/The+ONOS+CLI
## Switch : 
    a. to enable logging in bmv2 switch, rebuild the bmv2 switch with 
       ./configure --enable-debugger --with-pi 'CXXFLAGS=-O0 -g'  
       in the do_bmv2 function in the install-p4-tools.sh  
    b. to enable P4Runtime logs  
       comment the line cp ~/log.h ~/p4tools/p4runtime/proto/server/ 
       in scripts/install-p4-tools.sh and re-run it 
    c. to check the table entries in switch open switch cli using  
       simple_switch_grpc --thrift-port 9090 
       cli> table_dump <table_name>
