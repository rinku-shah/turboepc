sudo lxc-stop -n ran1 
sudo lxc-stop -n scale_dgw1 

sudo lxc-stop -n scale_sgw1_1 
sudo lxc-stop -n scale_sgw1_2 
sudo lxc-stop -n scale_sgw2_1 

sudo lxc-stop -n scale_pgw
sudo lxc-stop -n sink 

sleep 3
sudo lxc-ls --fancy
