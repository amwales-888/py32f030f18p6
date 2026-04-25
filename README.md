# py32f030f18p6
Simple breakout board for py32f030f18p6

- 3.3v LDO powered from 5V USB.
- UART connectivity to USB via ch340k optionally connected using jumpers.
- ARM SWD programming interface header.
- All other pins are broken out to headers.
- 1 LED optionally connected to pin PB5 using jumper.
- 1 Button optionally connected to pin PA8 using jumper.
- 1 Button connected to RESET pin, pulled high.
- Booloader selected by putting jumper across BOOT0 and 3v3 pins

<table>
  <tr>
    <td> <img src="Hardware/py32f030f18p6/KiCAD/images/py32f030f18p6-top.jpg"></td>
    <td> <img src="Hardware/py32f030f18p6/KiCAD/images/py32f030f18p6-bot.jpg"></td>
  </tr>
  <tr>
    <td> <img src="Hardware/py32f030f18p6/KiCAD/images/Capture-top.JPG"></td>
    <td> <img src="Hardware/py32f030f18p6/KiCAD/images/Capture-bot.JPG"></td>
  </tr>
</table>

Resources

<li>https://www.puyasemi.com/en/py32_series.html</li>
<li>https://www.eevblog.com/forum/microcontrollers/$0-11-py32f002a-m0-24mhz-320kb-actually-324kb-more-peripherals/</li>
<li>https://www.cnblogs.com/milton/p/18168592</li>
<li>https://github.com/IOsetting/py32f0-template/tree/main</li>
<li>https://www.cnblogs.com/milton/p/17111286.html</li>
<li>https://www.cnblogs.com/milton/p/18168592</li>
