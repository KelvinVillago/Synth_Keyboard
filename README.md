# Synth_Keyboard
Final Project for EE 329 class at Cal Poly SLO

The objective is to create an electronic synthesizer keyboard. There are 17 keys, enough for an octave and a half of notes. When the user presses one of the keys, the NUCLEO internally creates a sine wave and outputs it to the DAC. The output of the DAC is amplified through a push-pull amplifier to increase the current as the NUCLEO cannot supply enough current to meet the requirements of teh speakers. The output of the amplifier is sent to the speakers, which will play the corresponding note. 
