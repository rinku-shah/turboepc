1. This will be a 4 chain experiment with root ONOS serving attach/detach requests and local controllers serving Service Request/COntext Release requests.
2. The containers used are mentioned in the start/stop scripts of containers in this directory
3. We are using the modified switch contriners with multi-master support at DGW as well as  packet filtering code based on P4 dataplane reason_code to identify the controller to forward the packet to at P4Runtime Server.
4. The connect order of all switches to root controller is as follows : 
* DGW1 -> DGW2 -> DGW3 -> DGW4 -> PGW -> SGW1 -> SGW2 -> SGW3 -> SGW4
5. Then we need to run 'mirroring_add 500 1' command at all the SGWs switch CLI
