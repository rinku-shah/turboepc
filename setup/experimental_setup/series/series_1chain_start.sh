sudo lxc-start -n ran1 -d

sudo lxc-start -n scale_dgw1 -d

sudo lxc-start -n series_sgw1_1 -d
sudo lxc-start -n series_sgw1_2 -d
sudo lxc-start -n series_sgw2_2 -d

sudo lxc-start -n scale_pgw_series -d
sudo lxc-start -n sink -d

sleep 3
sudo lxc-ls --fancy
