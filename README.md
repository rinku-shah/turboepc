# turboepc
Accelerate mobile core network functions using hardware accelerators like programmable switches, and GPUs

# Designs:

traditional- All control plane messages serviced by Root controller, only GTP processing at switches.

basic- All offloadable messages (service request/context release/GTP processing) processed at the switch, and attach/detach at the Root controller. We consider that the user state is always available at the switch (always HIT).

parallel1miss- Single chain of RAN-DGW-SGW-PGW-SINK that considers HIT & MISS scenario at the SGW switch for UE context/state.

parallel2miss- Scale the EPC system- RAN-DGW-SGW-PGW-SINK with two instances of SGW in parallel working in offload mode.

series- RAN-DGW-SGW1-SGW2-PGW-SINK, i.e., two instances of SGW in series to scale the number of users in offload mode.

FT- Single chain of RAN-DGW-SGW-PGW-SINK with SGW-FT instance where the UE state is mirrored so that under failures the user state at the failed switch is not lost. This design also considers HIT & MISS scenario at the SGW switch for UE context/state.

HANDOVER- In this setup the user registers, establishes session with chain 2, handover is done over chain 1, delete the tunnel created over chain 2 (delete pending as of now). case 6 in ran.cpp is used for this scenario. For only handovers, service_request and s1_release flags are kept false. loop 1 and loop 2 values are set to be 1.

