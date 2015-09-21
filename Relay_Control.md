# Gebruik van de Raspberry Pi bij modelspoor
Om gebruikt te kunnen worden in de omgeving van een DCC modelbaan moeten we in staat zijn om DCC (25 Volt blokspanning) te schakelen. Daarvoor moeten we vanuit de Raspberry Pi direct, of indirect via andere chips die 3,3 Volt leveren, een relais aansturen. Nu trekken relais-spoelen (veel) meer stroom dan een GPIO pin kan leveren. Ook andere chips van dit (logic) niveau leveren niet het benodigde vermogen.

## Relais
We kunnen bijvoorbeeld kiezen voor een relais met een spoelspanning van 5 of 6 Volt. Die kunnen we zoals gezegd niet zomaar aansluiten. Allereerst moet er een aparte (5 Volt) voeding worden gebruikt om de relais te voeden. Dan moet de uitgangsspanning (3,3 Volt) worden omgezet naar die 5 Volt die het relais nodig heeft. Hieronder vind je een aantal resultaten van wat Googlen. 

#### Blussen
Bij het uitschakelen geeft een relais een relatief hoge spanningspiek. De rest van de schakeling wil je hiertegn beschermen, dat doe je met een zogeheten blusdiode. Deze blusdiode wordt antiparallel aan de relais- spoel geschakeld, om die uitschakel-stroom terug te voeren door de spoel, en niet in de rest van de schakeling.

#### LED indicator
In beide gevallen kunnen we een indicatie-LED toevoegen, in serie met een weerstand, maar nu parallel aan de relaispoel. Dit idee is te vinden in deze tekening uit [dit artikel](https://arduino-info.wikispaces.com/ArduinoPower) van arduino-info.wikispaces.

![bron: arduino-info.wikispaces](Relay_LED_Indicator.jpg)

Zoals je kunt zien, wordt hier een andere transistor genoemd, namelijk de BC847. Voor de ingangsweerstand wordt hier 10K gegeven. Me dunkt, nogal grote verschillen!


## Oplossingen

### Electronics Stack Exchange
Een oplossing die ik vond op Stack Exchange maakt gebruik van een transistor. De afbeelding hieronder komt uit [dit artikel](http://electronics.stackexchange.com/questions/56093/how-to-use-a-3v-output-to-control-a-5v-relay) van electronics.stackexchange: 

![bron: Electronics Stack Exchange](./ElecStackRelay.gif)

Dit artikel geeft geen waardes voor de componenten (weerstand en diode).


### Susa net
Een andere, soortgelijke oplossing komt van susa.net. Zie de afbeelding hieronder die hoort bij [dit artikel](http://www.susa.net/wordpress/2012/06/raspberry-pi-relay-using-gpio/):

![bron: susa.net](./Relay-Sample.png)

Zoals je ziet wordt hier de transistor benoemd: een BC337. Ook de weerstand krijgt een waarde: 1 Kilo Ohm; de tekst van het artikel geeft hierbij aan dat, als je strikt wilt zijn en onder 3 mA wilt blijven, je deze waarde moet verhogen naar 1,2K. De stroom wordt dan 2,75 mA.

## Componenten

### Relais
Ik vond bij Okaphone [dit relais](http://www.okaphone.com/artikel.asp?id=474062), artikelnummer `V23079-A1001-B301` van €6,95. Deze kan, met een 5 Volt spoel-spanning, 2A schakelen aan 250 Volt AC of 220 Volt DC. Zie ook deze afbeelding:

![bron: Okaphone](Relais_Okaphone.gif)

[Bij Farnell was dit relais ook te vinden](http://nl.farnell.com/te-connectivity-axicom/v23079-a1001-b301/relay-dpdt-5vdc-2a-tht/dp/4219960), maar dan voor €2,72:

![bron: nl.farnell.com](./Relais_Farnell.jpg)

### Transistoren
Genoemde mogelijkheden zijn:

* 'BC337', traditionele behuizing
* 'BC547', idem, maar levert max. 100mA, dus net te laag
* 'BC847', SMD, valt af.


### Diode
Maakt eigenlijk niet zoveel uit, de standaard `1N4007` volstaat.


## Conclusie
Ik ga na advies van Okaphone kiezen voor:

* het `V23079-A1001-B301` relais, 5V spoelspanning, met een spoel impedantie van 187 Ohm:
* de `BC337-16` (Old school, €0,25) 
* de `1N4007` als 'blus-diode' (€0,15)
* een 10K basisweerstand (€0,01)
* een 1K weerstand voor stroombegrenzing voor de indicatie LED (0,01)
* een groene indicatie LED `L934LGD` - stroom tot 5mA (€0,25)

Verder nodig:

* `MCP23017-E/SO` I2C 16 bit I/O expander (€2,45)

