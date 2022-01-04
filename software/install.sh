URL=""

wget $URL 


mkdir /opt/deepcool_rgb

mv deepcool_rgb /opt/deepcool_rgb/deepcool_daemon
chomd 755 /opt/deepcool_rgb/deepcool_daemon

echo /opt/deepcool_rgb/deepcool_daemon > /usr/bin/deepcool_rgb
chomd 755 /usr/bin/deepcool_rgb
echo add to startup from gui 
