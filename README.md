# intrusion_recorder
Arduino uno blynk app that time stamp records proximity intrusion with an HCSR04 and later HC-SR505

This project is to detect any intrution into a space and to record the time and distance from your object of interest.
This version uses the ultrasonic distance measurment device HCSR04 with an Arduino uno.  later plane is to replace or add the HC-SR505 to mark instrution points.  But that device only acts as on or off intrution without distance so might keep both as an option. For this project I used an arduino uno with wifi.

Later I would like to implement this with a esp-32.  With the esp-32 we can run in sleep mode with very little power so would be able to run with a battery for long term remote monitoring with no line power.  Also I have been able to implement OTA updates on other projects with the esp-32 with blynk that I can't do with the arduino uno.
 
I created this due to the problem I have looking through my surveillance video to find what caused some items going missing (my banana tree and some pipe fittings in this case).  So now I can look at this data on charts from each device to see time windows to take a closer look at to investigate what was going on.
 
 Note: I used blynk lib version 0.6.1 for this project.  I recall having some problems with the newer versions of blynk and had to settle on this version at the time.
