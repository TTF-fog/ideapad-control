## Ideapad Gaming Control
A tray application to be used for switching the different performance modes on an Ideapad Gaming 3/5 (For Linux)
The commands used for switching mode are described in a TOML file (example.toml) and sourced from
https://wiki.archlinux.org/title/Lenovo_IdeaPad_Gaming_3
Note:
This will crash on non 15ACH6 models, add your model code to laptops and make a new entry for it
eg.
```
[supported]
laptops = ["15ARH05"]
[15ARH05]

check_mode = "echo '\\\\_SB.PCI0.LPC0.EC0.SPMO' > /proc/acpi/call; cat /proc/acpi/call; printf '\\n'"
check_mode_backup = "echo '\\\\_SB.PCI0.LPC0.EC0.GZ44' > /proc/acpi/call; cat /proc/acpi/call; printf '\\n'"
performance_modes ={intelligent_cooling = "echo '\\\\_SB_.GZFD.WMAA 0 0x2C 2' > /proc/acpi/call",extreme_performance = "echo '\\\\_SB_.GZFD.WMAA 0 0x2C 3' > /proc/acpi/call", battery_saver = "echo '\\\\_SB_.GZFD.WMAA 0 0x2C 1' > /proc/acpi/call"}
rapid_charge = { turn_on = "echo '\\\\_SB.PCI0.LPC0.EC0.VPC0.SBMC 0x07' > /proc/acpi/call",turn_off = "echo '\\\\_SB.PCI0.LPC0.EC0.VPC0.SBMC 0x08' > /proc/acpi/call",status_check = "echo '\\\\_SB.PCI0.LPC0.EC0.QCHO' > /proc/acpi/call; cat /proc/acpi/call; printf '\\n'"}
battery_conservation = {turn_on = "echo '\\\\_SB.PCI0.LPC0.EC0.VPC0.SBMC 0x03' > /proc/acpi/call",turn_off = "echo '\\\\_SB.PCI0.LPC0.EC0.VPC0.SBMC 0x05' > /proc/acpi/call",status_check = "echo '\\\\_SB.PCI0.LPC0.EC0.BTSM' > /proc/acpi/call; cat /proc/acpi/call; printf '\\n'"}``
``
