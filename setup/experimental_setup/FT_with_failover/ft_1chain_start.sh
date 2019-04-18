sudo lxc-start -n ran1 -d

sudo lxc-start -n ft_dgw1 -d

sudo lxc-start -n ft_sgw1_1 -d
sudo lxc-start -n ft_sgw1_2 -d

sudo lxc-start -n scale_pgw -d
sudo lxc-start -n sink -d

sleep 3
sudo lxc-ls --fancy
