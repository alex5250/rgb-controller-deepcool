URL=""
PORT="/dev/ttyUSB0"

wget $URL 


mkdir /opt/deepcool_rgb

mv deepcool_rgb /opt/deepcool_rgb/deepcool_daemon
chmod 755 /opt/deepcool_rgb/deepcool_daemon

echo /opt/deepcool_rgb/deepcool_daemon $PORT > /usr/bin/deepcool_rgb 
chmod 755 /usr/bin/deepcool_rgb
echo add to startup from gui 
