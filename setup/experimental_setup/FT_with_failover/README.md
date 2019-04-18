1. This will be a 1 chain experiment with requests distributed between ROOT and local controllers.
2. The containers used are mentioned in the start/stop scripts of containers in this directory.
3. We are using the modified switch containers with multi-master support at DGW as well as  packet filtering code based on P4 dataplane `reason\_code` to identify the controller to forward the packet to at P4Runtime Server.
4. The connect order of all switches to root controller is as follows : 
* DGW1 -> SGW1 -> SGW2 -> PGW
5. Then we need to run 'mirroring\_add 500 2' command at SGW1 switch(primary switch) CLI
