1. This will be a 1 chain experiment with root ONOS serving all types of requests.
2. The containers used are mentioned in the start/stop scripts of containers in this directory
3. We are using the original contriners with no multi-master support at DGW or packet filtering code as it is not required in the centralized setup
4. The connect order of all switches to root controller is as follows : 
* DGW -> SGW -> PGW
