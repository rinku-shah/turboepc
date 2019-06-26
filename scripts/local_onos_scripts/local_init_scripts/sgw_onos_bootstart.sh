#!/bin/bash

echo now copying P4RuntimeFlowRuleProgrammable.java and P4RuntimeClientImpl.java to respective locations

cp P4RuntimeClientImpl.java ~/onos/protocols/p4runtime/ctl/src/main/java/org/onosproject/p4runtime/ctl/P4RuntimeClientImpl.java
cp P4RuntimeFlowRuleProgrammable.java ~/onos/drivers/p4runtime/src/main/java/org/onosproject/drivers/p4runtime/P4RuntimeFlowRuleProgrammable.java
echo copying run_onos.sh to onos direcotry
cp run_onos.sh ~/onos/
cd ~

git clone https://github.com/rinku-shah/turboepc.git


echo -------Manually replace modules.defs to include epc app and pipeconf---------------

 echo "insert '//apps/p4-tutorial/epc:onos-apps-p4-tutorial-epc-oar', in onos/modules.defs file "
 echo "insert  '//apps/p4-tutorial/pipeconf:onos-apps-p4-tutorial-pipeconf-oar', in onos/modules.defs file "
 echo "insert  '//apps/p4-tutorial/pipeconf_sgw1:onos-apps-p4-tutorial-pipeconf_sgw1-oar', in onos/modules.defs file "
 echo "insert  '//apps/p4-tutorial/pipeconf_sgw2:onos-apps-p4-tutorial-pipeconf_sgw2-oar', in onos/modules.defs file "
 echo "insert  '//apps/p4-tutorial/pipeconf_sgw3:onos-apps-p4-tutorial-pipeconf_sgw3-oar', in onos/modules.defs file "
 echo "insert  '//apps/p4-tutorial/pipeconf_pgw:onos-apps-p4-tutorial-pipeconf_pgw-oar', in onos/modules.defs file"   


 echo

echo now recompile onos by running:  buck build onos 


buck build onos