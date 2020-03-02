#/bin/bash
#https://stackoverflow.com/questions/35628656/how-execute-commands-as-another-user-during-provisioning-on-ubuntu
sudo -u ubuntu /bin/sh <<\DEVOPS_BLOCK
sudo apt install wireshark tcpdump git zip curl unzip python2.7 python-minimal -y
sudo apt-get install software-properties-common -y && \
sudo apt install openjdk-8-* -y
id
git clone https://gerrit.onosproject.org/onos
#cp -r /ubuntu/onos /home/ubuntu/
#https://docs.google.com/document/d/1E0eCw9-KaMFqQ4a-Zp3NGh07ognUKdkXYhqTYLB0S-M/edit
chown -R ubuntu:ubuntu onos
sudo apt install npm -y
DEVOPS_BLOCK

npm config set strict-ssl false
npm config set registry "http://registry.npmjs.org/"

sudo -u ubuntu /bin/sh <<\DEVOPS_BLOCK
#id
cd onos
#echo $HOME
#exporting HOME to ubuntu user to avoid .config accessing error 
export HOME=/home/ubuntu
#echo $HOME
git checkout onos-1.13
git pull
#pwd
cat << EOF >> /home/ubuntu/.bash_profile
#cat << EOF >> /home/ubuntu/.bashrc
export ONOS_ROOT="`pwd`"
exec bash
EOF

DEVOPS_BLOCK
sudo -u ubuntu /bin/bash <<\DEVOPS_BLOCK
. /home/ubuntu/.bash_profile 
#. /home/ubuntu/.bashrc
DEVOPS_BLOCK

sudo -u ubuntu /bin/bash <<\DEVOPS_BLOCK
#cat << EOF >> /home/ubuntu/.bash_profile
cat << EOF >> /home/ubuntu/.bashrc
source /home/ubuntu/onos/tools/dev/bash_profile
EOF

DEVOPS_BLOCK
sudo -u ubuntu /bin/bash <<\DEVOPS_BLOCK
. /home/ubuntu/.bash_profile 
#. /home/ubuntu/.bashrc
#exec bash
DEVOPS_BLOCK
echo "++++++++++++++++++++++++END OF INSTALL_ONOS SCRIPT++++++++++++++++++++++++"
#! /bin/bash
#we need bash shell here as we are including source of onos bash_profile and bashrc
sudo -u ubuntu /bin/bash <<\DEVOPS_BLOCK
#id says that the script is run as ubuntu user
id
echo $PATH
#exec bash
pwd
cd /home/ubuntu/onos
#cd $ONOS_ROOT
pwd
#exec bash
#shopt -s expand_aliases
#source to bashrc does not include the inner source reference file somehow
source /home/ubuntu/.bashrc
#the workaround to this isse is to directly source the file here 
source /home/ubuntu/onos/tools/dev/bash_profile

#as this is a non-interactive shell we cannot source the bash_profile here, if we do the scipt stops execution at this point
#source /home/ubuntu/.bash_profile
#now the path variable contains all the onos binary files path as well as we have sourced the onos bash_profile above
#echo $PATH
# this command will setup the p4 tools(bmv2, p4c, bmv2 targets(simple_switch_grpc), protobuf, p4runtime etc) in the home directory of ubuntu user 
#onos-setup-p4-dev
onos-buck build onos
pwd
DEVOPS_BLOCK
echo "++++++++++++++++++++++++END OF INSTALL_P4TOOLS_ONOS SCRIPT++++++++++++++++++++++++"

