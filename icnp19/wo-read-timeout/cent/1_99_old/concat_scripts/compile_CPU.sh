#ROOT RAN DGW SGW PGW
paste ../ran1_util.txt |tr -s "," " "|tr -s [:blank:] " " > tmp
cat tmp| tail -n +2 > tmp_cpu
awk -f compile_CPU.awk tmp_cpu > ran_cpu.dat

paste ../dgw1_util.txt |tr -s "," " "|tr -s [:blank:] " " > tmp
cat tmp| tail -n +2 > tmp_cpu
awk -f compile_CPU.awk tmp_cpu > dgw_cpu.dat

paste ../sgw11_util.txt |tr -s "," " "|tr -s [:blank:] " " > tmp
cat tmp| tail -n +2 > tmp_cpu
awk -f compile_CPU_scale.awk tmp_cpu > sgw_cpu.dat

cat ../pgw_util.txt| tail -n +2 > tmp_cpu
awk -f compile_CPU.awk tmp_cpu > pgw_cpu.dat

cat ../controller_util.txt| tail -n +2 > tmp_cpu
awk -f compile_CPU.awk tmp_cpu > root_cpu.dat

echo "#UE ROOT DGW SGW PGW RAN" > ../results/all_cpu.dat
paste  root_cpu.dat dgw_cpu.dat sgw_cpu.dat pgw_cpu.dat ran_cpu.dat |tr -s "," " "|tr -s [:blank:] " "| awk '{print $1, $2, $4, $6, $8, $10}' >> ../results/all_cpu.dat
