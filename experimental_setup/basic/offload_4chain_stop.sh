#!/bin/bash

# Usage: ./terminals.sh
# Do not run as superuser

# Start the containers

sudo lxc-stop -n offload_ran1 
sudo lxc-stop -n offload_ran2 
sudo lxc-stop -n offload_ran3 
sudo lxc-stop -n offload_ran4 
sudo lxc-stop -n offload_dgw1 
sudo lxc-stop -n offload_dgw2 
sudo lxc-stop -n offload_dgw3 
sudo lxc-stop -n offload_dgw4 
sudo lxc-stop -n offload_sgw1 
sudo lxc-stop -n offload_sgw2 
sudo lxc-stop -n offload_sgw3 
sudo lxc-stop -n offload_sgw4 
sudo lxc-stop -n pgw 
sudo lxc-stop -n sink 
sudo lxc-ls --fancy
