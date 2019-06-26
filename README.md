# TurboEPC
Accelerate mobile core network control plane functions using programmable switches

# Designs:

traditional- All control plane messages serviced by Root controller, only GTP processing at switches.

basic- All offloadable messages (service request/context release/GTP processing) processed at the switch, and attach/detach at the Root controller. We consider that the user state is always available at the switch (always HIT).

parallel1miss- Single chain of RAN-DGW-SGW-PGW-SINK that considers HIT & MISS scenario at the SGW switch for UE context/state.

parallel2miss- Scale the EPC system- RAN-DGW-SGW-PGW-SINK with two instances of SGW in parallel working in offload mode.

series- RAN-DGW-SGW1-SGW2-PGW-SINK, i.e., two instances of SGW in series to scale the number of users in offload mode.

FT- Single chain of RAN-DGW-SGW-PGW-SINK with SGW-FT instance where the UE state is mirrored so that under failures the user state at the failed switch is not lost. This design also considers HIT & MISS scenario at the SGW switch for UE context/state.

HANDOVER- In this setup the user registers, establishes session with chain 2, handover is done over chain 1, delete the tunnel created over chain 2 (delete pending as of now). case 6 in ran.cpp is used for this scenario. For only handovers, service_request and s1_release flags are kept false. loop 1 and loop 2 values are set to be 1.

# Roadmap

Installation steps :
Please follow steps from turboepc/installation_steps.txt

traditional - 
 code location: turboepc/modular_p4_codes/4chaincode/traditional/

basic - 
 code location: turboepc/modular_p4_codes/4chaincode/basic

parallel - 
 code location: turboepc/modular_p4_codes/4chain_3sgwscode/parallel/

series -  
 code location: turboepc/modular_p4_codes/4chain_3sgwscode/series/

handover -
 code location: turboepc/handover/

FT -
code location: turboepc/modular_p4_codes/1chaincode/FT_with_failover/
 
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