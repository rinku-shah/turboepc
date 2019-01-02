# turboepc
Accelerate mobile core network functions using hardware accelerators like programmable switches, and GPUs

# Designs:

centralized- All control plane messages serviced by Root controller, only GTP processing at switches.

offload- All offloadable messages (service request/context release/GTP processing) processed at the switch, and attach/detach at the Root controller. We consider that the user state is always available at the switch (always HIT).

scale1miss- Single chain of RAN-DGW-SGW-PGW-SINK that considers HIT & MISS scenario at the SGW switch for UE context/state.

scale2miss- Scale the EPC system- RAN-DGW-SGW-PGW-SINK with two instances of SGW in parallel working in offload mode.

seriesOffload- RAN-DGW-SGW1-SGW2-PGW-SINK, i.e., two instances of SGW in series to scale the number of users in offload mode.

FaultTolerantOffload- Single chain of RAN-DGW-SGW-PGW-SINK with SGW-FT instance where the UE state is mirrored so that under failures the state is not lost. This design also considers HIT & MISS scenario at the SGW switch for UE context/state.

