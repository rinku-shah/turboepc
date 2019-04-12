#ROOT RAN DGW SGW PGW
paste ../ran1_util.txt ../ran2_util.txt ../ran3_util.txt ../ran4_util.txt |tr -s "," " "|tr -s [:blank:] " " > tmp
cat tmp| tail -n +2 > tmp_cpu
awk -f compile_CPU.awk tmp_cpu > ran_cpu.dat

paste ../dgw1_util.txt ../dgw2_util.txt ../dgw3_util.txt ../dgw4_util.txt |tr -s "," " "|tr -s [:blank:] " " > tmp
cat tmp| tail -n +2 > tmp_cpu
awk -f compile_CPU.awk tmp_cpu > dgw_cpu.dat

paste ../sgw11_util.txt ../sgw12_util.txt ../sgw21_util.txt ../sgw22_util.txt ../sgw31_util.txt ../sgw32_util.txt ../sgw41_util.txt ../sgw42_util.txt  |tr -s "," " "|tr -s [:blank:] " " > tmp
cat tmp| tail -n +2 > tmp_cpu
awk -f compile_CPU_scale.awk tmp_cpu > sgw_cpu.dat

cat ../pgw_util.txt| tail -n +2 > tmp_cpu
awk -f compile_CPU.awk tmp_cpu > pgw_cpu.dat

cat ../controller_util.txt| tail -n +2 > tmp_cpu
awk -f compile_CPU.awk tmp_cpu > root_cpu.dat

echo "#UE ROOT DGW SGW PGW RAN" > ../results/all_cpu.dat
paste  root_cpu.dat dgw_cpu.dat sgw_cpu.dat pgw_cpu.dat ran_cpu.dat |tr -s "," " "|tr -s [:blank:] " "| awk '{print $1, $2, $4, $6, $8, $10}' >> ../results/all_cpu.dat
