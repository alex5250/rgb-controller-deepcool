# rgb-controller-deepcool
Simple software that sets color in dependence of temperature of cpu in pc 
Installation : 
Download ardino ide 
Open the firmware.ino and flash it inside arduino (D8,D5 is just and example) 
# On Linux only 
get via curl the install.sh like that 
```Bash
curl https://raw.githubusercontent.com/alex5250/rgb-controller-deepcool/main/software/install.sh > install.sh && chmod 755 install.sh
```
Run it with sudo 
```Bash
sudo ./install.sh
```
Last and not least using GUI add  to startup deepcool_rgb . 
