Fault Tolerant Code (Sync mode):
1. All code changes are annotated with @FT_with_failover
2. The P4 code is topology specific. Toplogy is attached in file FTTopology.jpg
3. Use "mirroring_add 500 2" for cloning purpose at SGW1_1 as SR' cloned packet has to be sent to SGW1_2
