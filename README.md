# :bulb: Telegram on esp8266
I used Telegram to control an esp8266 LED, I did this by creating a Telegram bot and using the Universal Telegram Bot Library to interact with my bot through Arduino.

## 1. Creating a Telegram Bot. :robot:
I followed a manual from ElectroRules (https://www.electrorules.com/telegram-control-esp32-esp8266-output), because it was one of the more recent ones I could find when Googeling 'telegram on esp8266', it was written on March 8, 2022.
After installing Telegram, I opened the app and search for "botfather". Here I typed **/newbot** and gave my bot a name: Ledbot. After creating a bot you receive a message with your bot token.

<img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/Botfathersearch.png" width=25% height=25%> <img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/Botfather.png" width=25% height=25%> <img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/Newbot.png" width=25% height=25%>

## 2. Get your Telegram user ID. :raising_hand:
Then I had to get my Telegram user ID, so that the bot knows what messages are coming from my account. The manual I was following (https://www.electrorules.com/telegram-control-esp32-esp8266-output) told me to search for IDBot and type **/getid** to get my user ID. 

### Error :triangular_flag_on_post:
I couldn't find 'IDBot' but I did see a channel called 'ID Bot news', where there was a pinned message talking about @usernametoidbot. Clicking this link finally send me to a chat with ID Bot, where it immediately gave me my user id after pressing Start.

<img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/IDbot.png" width=25% height=25%> <img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/group.png" width=25% height=25%> <img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/IDbot2.jpg" width=25% height=25%>

## 3. Universal Telegram Bot Library. :package:
To interact with the Telegram bot I needed to install a library called Universal Telegram Bot Library by Brian Lough. 
I searched for it in the Arduino Library Manager and installed the lastest version. You can also download the zip file from https://www.arduinolibraries.info/libraries/universal-telegram-bot and include it in your project in the Sketch tab.

<img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/library.PNG" width=20% height=20%> <img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/addlib.PNG" width=40% height=40%>

## 4. Code. :crystal_ball:
After installing the library, I copied this code into my sketch:

<img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/code1.PNG" width=30% height=30%> <img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/code2.PNG" width=28.5% height=28.5%> <img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/code3.PNG" width=35% height=35%>

To make this code work for me I had to insert my Bot token, user ID, and network credentials (SSID and password). 

### What does this code do?
This code checks for new messages every second, it then also checks the chat_id to see if the message is from you or if it should be ignored. If it's from you, it saves the message in a text variable and checks its content, and when it receives the **/led_on** message it turns on the LED and sends a confirmation message.

## 5. Upload. :inbox_tray:
Before you upload the code to your board, check if the right board and port are selected under Tools. After uploading you can turn your LED on and off by talking to your bot on Telegram: **/led_on** turns the LED on, **/led_off** turns the LED off and **/state** requests the current LED state.

<img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/signal-2022-10-11-200737_003.jpeg" width=30% height=30%>

Nice, the code works! :tada:

### Error :triangular_flag_on_post:
Now the blue led on the board turns on and off, BUT when is says ON it's actually OFF and vice versa. Why does this happen?
The ElectroRules manual says this:
> "The on-board LED should turn on and turn off accordingly (the ESP8266 on-board LED works in reverse, it’s off when you send /led_on and on when you send /led_off)."

So, I should send a LOW signal to turn the LED on and a HIGH signal to turn it off. I can change these values in the code so it makes more sense when communicating it on Telegram:

<img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/lowhighbad.PNG" width=45% height=45%> <img src="https://github.com/rarooij98/telegram-on-esp8266/blob/main/images/lowhighgood.PNG" width=45% height=45%>


## Sources :card_file_box:
- https://www.electrorules.com/telegram-control-esp32-esp8266-output
- https://www.arduinolibraries.info/libraries/universal-telegram-bot
