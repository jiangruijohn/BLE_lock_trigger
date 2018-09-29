## Mobile Checkin : Make a door unlocker with Arduino pro micro + Bluetooth 4.0 (BLE) 




### Goal

Automatically unlock & lock the door after verifying the passcode and command received via bluetooth 





### Features

 - Automatically unlock the door if people walk close to the door from inside of the room 
   <p><img src="https://i.imgur.com/qSOt17l.png" alt="Commercial Photography" width="360" height="270"></p>
    
 - For people want to get into the room from outside, this device can receive passcode and command via bluetooh, verify eligibility and trigger unlocking function
   <p><img src="https://i.imgur.com/oyN3i4u.png" alt="Commercial Photography" width="360" height="270"></p>
   
 - Display working status in OLED
 - Working in 4 modes: unlock once with 3 seconds delay, keep unlock with timer set, alway unlock until lock command, lock.
    




### Hardwares
 #### 1. List
  - Arduino ( pro micro )
  - Bluetooth 4.0 module (BLE)
  - PIR Sensor
  - Relay
  - Adafruit OLED(SPI 128*64)
  - Jump wires
 #### 2. Connecting Hardwares
  <p><img src="https://i.imgur.com/5BfPbSh.png" alt="Commercial Photography"></p>
    




### About Client App
   For testing, please use any mobile app that can send bluetooth data. such as <a href="https://itunes.apple.com/us/app/lightblue-explorer/id557428110?mt=8">LightBlue</a>
   <p>***BLE_Lock_Trigger*** is a part of Mobile Checkin project. This device is to be connected to a hardware router ( Raspberry Pi) via bluetooth. Besides of these, the whole project consist of another 2 parts: </p>
  <p>  - Mobile Application (wechat miniApp so far) as client.     </p>
  <p>  - Micro-Service Server as an agent working between hardware routers and Mobile Application.</p>
   
