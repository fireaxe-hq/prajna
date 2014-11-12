mkdir -p prajna
tftp -g -l prajna/prajna_k.ko -r prajna_k.ko 192.168.2.100
tftp -g -l prajna/paramita -r bin/paramita 192.168.2.100
tftp -g -l prajna/skandhas -r bin/skandhas 192.168.2.100

insmod prajna/prajna_k.ko

chmod 777 -R prajna
major=$(cat /proc/devices | grep prajna_k | grep -Eo "[0-9]*")
mknod /dev/prajna_k c $major 0

