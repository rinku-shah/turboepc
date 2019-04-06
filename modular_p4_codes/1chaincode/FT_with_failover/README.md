Fault Tolerant Code (Sync mode):
1. All code changes are annotated with @FT_with_failover
2. The P4 code is topology specific. Toplogy is attached in file FT_with_failover.pdf
3. Use "mirroring_add 500 2" for cloning purpose at SGW1_1 as SR' cloned packet has to be sent to SGW1_2
4. When SR' reaches SGW1_2 then the local ONOS running on SGW1_2 populates the state and forwarding tables and then replies back to RAN(SR''). The SR'' is then forwarded back to RAN via SGW1_1
5. Once the primary SGW crashes then the root controller toggles the control plance and data plane traffic forwarding port at DGW to send packets directly to backup SGW.
6. Primary SGW is SGW1_1 and backup SGW is SGW1_2
7. Root ONOS controller populates forarding tables and offload state tables onto both primary and backup SGWs during Attach 

