#!/bin/bash
#echo $0
cur_dir=`pwd`
echo current dir = $cur_dir
cd ~
sudo apt-get install mysql-server -y
echo
echo

echo Login to MySql.
echo "$ mysql -u root -proot"
echo "Create a database named HSS.
#mysql> create database HSS;
#Logout from MySql and run the following command from where the file HSS.sql is located (can be found under /src/controller/HSS).
#$ mysql -u root -proot HSS < HSS.sql"

echo 
echo ----------------------------------------------
echo ' "mysql":"mvn:mysql:mysql-connector-java:5.1.35", to artifacts in lib/deps.json '
echo 'then cd ~  && cd onos '
echo 'then run onos-lib-gen'
echo ----------------------------------------------

git clone https://github.com/rinku-shah/turboepc.git

echo
echo

echo copying run_onos.sh to onos direcotry
cp $cur_dir/run_onos.sh ~/onos/

# cd ~ && cd onos
#!/bin/bash
#insert '//apps/p4-tutorial/epc:onos-apps-p4-tutorial-epc-oar', in modules.defs file but this is not working will fix it later
# match=' # Apps'
# insert=''//apps/p4-tutorial/epc:onos-apps-p4-tutorial-epc-oar','
# file='modules.defs'
# sed "s/$match/$match\n$insert/" $file

echo -------Manually replace modules.defs to include epc app and pipeconf---------------

 echo "insert '//apps/p4-tutorial/epc:onos-apps-p4-tutorial-epc-oar', in onos/modules.defs file "
 echo "insert  '//apps/p4-tutorial/pipeconf:onos-apps-p4-tutorial-pipeconf-oar', in onos/modules.defs file "
 echo "insert  '//apps/p4-tutorial/pipeconf_sgw1:onos-apps-p4-tutorial-pipeconf_sgw1-oar', in onos/modules.defs file "
 echo "insert  '//apps/p4-tutorial/pipeconf_sgw2:onos-apps-p4-tutorial-pipeconf_sgw2-oar', in onos/modules.defs file "
 echo "insert  '//apps/p4-tutorial/pipeconf_sgw3:onos-apps-p4-tutorial-pipeconf_sgw3-oar', in onos/modules.defs file "
 echo "insert  '//apps/p4-tutorial/pipeconf_pgw:onos-apps-p4-tutorial-pipeconf_pgw-oar', in onos/modules.defs file"   


 echo
 echo "comment #'//apps/p4-tutorial/mytunnel:onos-apps-p4-tutorial-mytunnel-oar', in same file:"


echo now copying P4RuntimeFlowRuleProgrammable.java and P4RuntimeClientImpl.java to respective locations
cp $cur_dir/P4RuntimeClientImpl.java ~/onos/protocols/p4runtime/ctl/src/main/java/org/onosproject/p4runtime/ctl/
cp $cur_dir/P4RuntimeFlowRuleProgrammable.java ~/onos/drivers/p4runtime/src/main/java/org/onosproject/drivers/p4runtime/


echo "once all switches are connected run  app activate org.onosproject.p4tutorial.epc on onos-cli(run onos localhost on a terminal to get cli)"






