# :bulb: Telegram on esp8266
I used Telegram to control an esp8266 LED, I did this by creating a Telegram bot and using the Universal Telegram Bot Library to interact with my bot through Arduino.

## 1. Creating a Telegram Bot. :robot:
I followed a manual from ElectroRules (https://www.electrorules.com/telegram-control-esp32-esp8266-output), because it was one of the more recent ones I could find when Googeling 'telegram on esp8266', it was written on March 8, 2022.
After installing Telegram, I opened the app and search for "botfather". Here I typed **/newbot** and gave my bot a name: Ledbot. After creating a bot you receive a message with your bot token.

![Botfather](images/botfather.png)
![Newbot](images/newbot.png)

## 2. Get your Telegram user ID. :raising_hand:
Then I had to get my Telegram user ID, so that the bot knows what messages are coming from my account. The manual I was following (https://www.electrorules.com/telegram-control-esp32-esp8266-output) told me to search for IDBot and type **/getid** to get my user ID. I couldn't find 'IDBot' but I did see a channel called 'ID Bot news', where there was a pinned message talking about @usernametoidbot. Clicking this link finally send me to a chat with ID Bot, where it immediately gave me my user id after pressing Start.

![IDBot](images/idbot.png)
![IDBot2](images/idbot2.ng)

## 3. Universal Telegram Bot Library. :package:
To interact with the Telegram bot I needed to install a library called Universal Telegram Bot Library by Brian Lough. 
I searched for it in the Arduino Library Manager and installed the lastest version.

## 4. Code. :crystal_ball:
After installing the library, I copied this code into my project:

![Code](images/code.png)

To make this code work for me I had to insert my Bot token, user ID, and network credentials (SSID and password). This code checks for new messages every second, it then also checks the chat_id to see if the message is from you or if it should be ignored. If it's from you, it saves the message in a text variable and checks its content, and when it receives the **/led_on** message it turns on the LED and sends a confirmation mesage.

## 5. Upload. :inbox_tray:
Before you upload the code to your board, check if the right board and port are selected under Tools. After uploading you can turn your LED on and off by talking to your bot on Telegram: **/led_on** turns the LED on, **/led_off** turns the LED off and **/state** requests the current LED state.

![Bot](images/bot.png)

### Error 1 :triangular_flag_on_post:
But when I send **/led_on**, my LED stayed off. So I tried asking for the **/state**, and it replied that the state of the LED was ON, while I could clearly see that the LED was off. 
To solve this I tried resetting my board but nothing changed. My serial monitor says that it's connected to wifi, but just to be sure I switched from 4G to 2G and then 5G, which didn't work. I also dubble checked if my bot token en user id were correct and they were.

What exactly happens in the code when I send **/led_on**? The state is changed but not the LED itself, why? 

```
if (text == "/led_on") {
      bot.sendMessage(chat_id, "LED state set to ON", "");
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
}
```

At line 33, ledPin was defined as 2 and the ledState was defined as LOW. I think that means that the default value for the LED, when you start running the code, is for it to be off. And the ledPin we're controlling is GPIO 2, the build-in esp8266 LED. That all makes sense.

So then I looked up some other manuals to see if they've done anything different. A manual by Random Nerd Tutorials (https://randomnerdtutorials.com/telegram-group-esp32-esp8266) shows you a big, orange warning sign telling you to NOT install the Universal Telegram Bot Library through the Arduino Library Manager, because it may be a deprecated version:

![Lib](images/lib.png)

Oops. I downloaded the zip of the library from https://www.arduinolibraries.info/libraries/universal-telegram-bot and included it in my Arduino sketch like so:

![Zip](images/zip.png)

Now the code works! :tada:

### Error 2 :triangular_flag_on_post:
Now the blue led on the board turns on and off, BUT when is says ON it's actually OFF and vice versa. Why does this happen?
The ElectroRules manual says this:
> "The on-board LED should turn on and turn off accordingly (the ESP8266 on-board LED works in reverse, it’s off when you send /led_on and on when you send /led_off)."

So, I should send a LOW signal to turn the LED on and a HIGH signal to turn it off. I can change these values in the code so it makes more sense when communicating it on Telegram:

![Low](images/low.png) 

## Sources :card_file_box:
- https://www.electrorules.com/telegram-control-esp32-esp8266-output
- https://randomnerdtutorials.com/telegram-group-esp32-esp8266
- https://www.arduinolibraries.info/libraries/universal-telegram-bot
