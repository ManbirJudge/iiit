mkdir out
for dt in 0.5 1.0 2.0; do
    rm -r "out/out_$dt"
    mkdir -p "out/out_$dt"
    dt="$dt" namd3 +p12 nve.namd > "out/out_$dt/nve.log"
done