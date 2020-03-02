make -C apps/p4-tutorial/pipeconf/src/main/resources
make -C apps/p4-tutorial/pipeconf_sgw1/src/main/resources
make -C apps/p4-tutorial/pipeconf_sgw2/src/main/resources
make -C apps/p4-tutorial/pipeconf_sgw3/src/main/resources
make -C apps/p4-tutorial/pipeconf_pgw/src/main/resources
 ONOS_APPS=drivers.bmv2,p4tutorial.pipeconf,p4tutorial.pipeconf_sgw1,p4tutorial.pipeconf_sgw2,p4tutorial.pipeconf_sgw3,p4tutorial.pipeconf_pgw NO_BUCKD=1 onos-buck run onos-local -- clean
