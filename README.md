It's simple custom application for [VESC](http://vedder.se/) BLDC controller, used in DPV upgrade project

It is used with BA34-C-300 motor. Motor params:
````
    Ke = 18V/krpm
    Kt = 24.3 in-oz/amp
    Ra ( L - L ) = .34 ohms
    Ind  ( L - L ) = 1.08 mhy
    No Load amps ~ .65 A
````

I've used firmware version 2.8 and hardware version 4.10. Ho serious changed to original board, just changed 1mOhm resistors to 3W, because could not find 7W version on DK. Here is the [BOM](https://www.digikey.com/classic/RegisteredUser/BOMBillOfMaterials.aspx?path=1&exist=1&id=3160668) from DigiKey (available for registered users only).


Since modifying DPV uses reed switch I just wrote simple custom application for VESC. It cycles between 70%, 100% and 50% of duty cycle. 

The wireing is simple. I connected reed switch to +3.3V and GND, and tied reed output to TX_SDA (just like in Vedder's [sample app](http://vedder.se/2015/08/vesc-writing-custom-applications/), but without ADC part).

Motor XLM config also included. I've used [Jacob Bloy's BLDC toold build for OSX](https://drive.google.com/folderview?id=0Bym9XrdeViekfkRETmRndENkcVpySW5sWjIzOWdrLThCY01HY3BPOXpqYVRHUlQxS0R5ZlU) to flash firmware and Linux Mint to compile everything else. No suprises during compilation - everything woked smoothly. Thanks, Benjamin :)
