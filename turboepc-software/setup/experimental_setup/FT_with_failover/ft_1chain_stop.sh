sudo lxc-stop -n ran1 

sudo lxc-stop -n ft_dgw1 

sudo lxc-stop -n ft_sgw1_1 
sudo lxc-stop -n ft_sgw1_2 

sudo lxc-stop -n scale_pgw 

sleep 3
sudo lxc-ls --fancy
