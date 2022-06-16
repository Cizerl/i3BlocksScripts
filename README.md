# i3BlocksScripts

###### Following Scripts/Programs are working on my Lenovo Thinkpad-T480 with Debian and i3 written for i3Blocks.

If you want to use the C Programs you need to to compile them once. Example:
```
gcc [programName].c -o programName
**Battery-Example**
gcc BatteryBlock.c -o BatteryBlock
```
You can then use them in the i3Blocks Config like this:
```
[my_battery]
command=/home/your_user/.config/i3/ScriptFolderName/batteryBlock
markup=pango
interval=5 
```


### Project-Dependencies:

|   | FontAwesome-Icons installed | light installed |
|---|:-:|:-:|
| Battery-Module | :heavy_check_mark: | - | 
| Temperature-Module | :heavy_check_mark: | - |
| Disk-Module | :heavy_check_mark:  |  - |
| Brightness-Module | - |  :heavy_check_mark: |


## Battery-Module

The battery module displays the current charge percent of your battery/batteries. 
The exponent next to the battery icon is used to indicate how many batteries are currently used:
 * **One Battery:** ![One Battery](/images/singleBattery80.png) &nbsp;&nbsp;&nbsp; **Two Batteries:** ![Two Batteries](/images/battery80.png)

If the battery/batteries are charging, the color and icon changes:
 * ![Charging](/images/batteryPlug.png)

The icon and the color changes depending on the charge levels. If its charging the color is always green.

| Charge | Icon/Color |
|:-:|:-:|
|100% - 85%|![](/images/battery90.png)|
|85% - 65%|![](/images/battery80.png)|
|65% - 40%|![](/images/battery60.png)|
|40% - 30%|![](/images/battery35.png)|
|30% - 20%|![](/images/battery25.png)|
|20% - 10%|![](/images/battery15.png)|
|10% - 0%|![](/images/battery5.png)|


## Temperature-Module

The temperature-module displays the current cpu temperature. But you can easily change the path in the code for it to display other thermal_zones of your system.
The icon and the color changes depending on the temperature.

| Temperature | Icon/Color |
|:-:|:-:|
| +0°C |![](/images/temp40.png)|
| +50°C |![](/images/temp50.png)|
| +60°C |![](/images/temp60.png)|
| +70°C |![](/images/temp70.png)|
| +80°C |![](/images/temp80.png)|
| +90°C |![](/images/temp90.png)|

## Disk-Module

The disk-module displays the current available free hard drive space. It is only written for one drive since I use it on a laptop, but it shouldn't be too difficult to expand for multi-drive usage. The space is displayed in gigabytes(*GB*) but in the code, I commented how to adapt it for gibibyte(*GiB*).
Low disk Space is displayed in different colors.

| Free Space | Icon/Color |
|:-:|:-:|
| standard |![](/images/disk.png)|
| <15% |![](/images/disk60.png)|
| <10% |![](/images/disk40.png)|
| <5% |![](/images/disk20.png)|
| <2.5% |![](/images/disk10.png)|


## Brightness-Module

For the brightness Shell-Script to work you need **[light](https://github.com/haikarainen/light)** installed. It is available in many official repos, so look there first for an easy installation.

![Example-Brightness](/images/brightnessLevel.png)