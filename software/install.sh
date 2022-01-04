URL="https://github.com/alex5250/rgb-controller-deepcool/releases/download/v0.01/linux_rgb_daemon"
PORT="/dev/ttyUSB0"

wget $URL 


mkdir /opt/deepcool_rgb

mv linux_rgb_daemon /opt/deepcool_rgb/deepcool_daemon
chmod 755 /opt/deepcool_rgb/deepcool_daemon

echo /opt/deepcool_rgb/deepcool_daemon $PORT > /usr/bin/deepcool_rgb 
chmod 755 /usr/bin/deepcool_rgb
echo add to startup from gui 
rm -rf linux_rgb_daemon
rm -rf install.sh
