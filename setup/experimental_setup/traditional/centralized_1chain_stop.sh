#!/bin/bash

# Usage: ./terminals.sh
# Do not run as superuser

# Start the containers

sudo lxc-stop -n ran1
sudo lxc-stop -n dgw1
sudo lxc-stop -n sgw1 
sudo lxc-stop -n pgw 
sudo lxc-stop -n sink 
sudo lxc-ls --fancy

