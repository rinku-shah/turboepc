1. This will be a 1 chain experiment with 3SGWs in 1 chain and root ONOS serving attach/detach requests and local controllers serving Service Request/Context Release requests.
2. The containers used are mentioned in the start/stop scripts of containers in this directory
3. We are using the modified DGW/SGW switch contriners with multi-master support at as well as packet filtering code based on P4 dataplane reason_code to identify the controller to forward the packet to at P4Runtime Server.
4. The connect order of all switches to root controller is as follows : 
* DGW1 -> SGW1 -> SGW2 -> SGW3 -> PGW
5. Then we need to run 'mirroring_add 500 1' command at all the SGWs switch CLI
