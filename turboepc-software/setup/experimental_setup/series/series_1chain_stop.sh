
sudo lxc-stop -n ran1

sudo lxc-stop -n scale_dgw1 

sudo lxc-stop -n series_sgw1_1 
sudo lxc-stop -n series_sgw1_2 
sudo lxc-stop -n series_sgw2_2

sudo lxc-stop -n scale_pgw_series
sudo lxc-stop -n sink 

sleep 3
sudo lxc-ls --fancy
