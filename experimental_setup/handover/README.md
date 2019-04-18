1. This will be a 2 chain experiment with root ONOS serving Attach/Detach/Handover requests and local controller serving Context Relase/Service Reuqest requests.
2. The containers used are mentioned in the start/stop scripts of containers in this directory
3. The same containers are used for both centralized and handover experiments of handover
4. We are using the modified switch contriners with multi-master support at DGW as well as  packet filtering code based on P4 dataplane reason_code to identify the controller to forward the packet to at P4Runtime Server.
5. The connect order of all switches to root controller is as follows : 
* DGW1 -> SGW1 -> SGW2 -> DGW2 -> PGW
6. Then we need to run 'mirroring_add 500 1' command at all the SGWs switch CLI
