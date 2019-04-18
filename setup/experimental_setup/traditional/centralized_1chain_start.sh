#!/bin/bash

# Usage: ./terminals.sh
# Do not run as superuser

# Start the containers

sudo lxc-start -n ran1 -d
sudo lxc-start -n dgw1 -d
sudo lxc-start -n sgw1 -d
sudo lxc-start -n pgw -d
sudo lxc-start -n sink -d
sudo lxc-ls --fancy

