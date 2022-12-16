cd libp2p && make && cd ..
cd liblmdb && make && cd ..
cd libipfs && make && cd ..

gcc -O2 -I./ main.c -o main */*.a -lcurl
