import schemdraw
import schemdraw.elements as elm

def draw_engineering_schematic():
    # Initialize a drawing with a clean black-and-white style
    with schemdraw.Drawing(file='pot_engineering_schematic.png', show=False) as d:
        # d.config(unit=2.5, lw=1.5, font='Courier')
        
        # -------------------------------------------------------------------------
        # 1. THE POWER RAIL & POTENTIOMETER SYMBOL
        # -------------------------------------------------------------------------
        # Start at the top with a 3.3V Power Source symbol
        d += (VCC := elm.Vdd().label('+3.3V (From Teensy)', 'right'))
        
        # Draw a wire straight down to the top terminal of the potentiometer (Pin 3)
        d += elm.Line().down().length(0.75)
        
        # Draw the standard zigzag potentiometer symbol (facing right)
        d += (POT := elm.Potentiometer().down().label('B10K\nPot', 'left'))
        
        # Draw a wire from the bottom terminal (Pin 1) down to a Ground symbol
        d += elm.Line().down().length(0.75)
        d += elm.Ground()
        
        # Text annotations for the outer pot hardware pins
        d += elm.Label().at(POT.start).label('[Pin 3]', 'right', fontsize=9)
        d += elm.Label().at(POT.end).label('[Pin 1]', 'right', fontsize=9)

        # -------------------------------------------------------------------------
        # 2. THE WIPER SIGNAL ROUTE
        # -------------------------------------------------------------------------
        # Move to the middle wiper terminal (Pin 2)
        d += elm.Line().right().at(POT.tap).length(1.5).label('[Pin 2]\n(Wiper)', 'top', fontsize=9)
        
        # -------------------------------------------------------------------------
        # 3. THE TEENSY 4.1 INPUT TERMINAL
        # -------------------------------------------------------------------------
        # Draw a clean integrated circuit pin block representing the target input
        d += (TEENSY_PIN := elm.Box(w=2.5, h=1.5).anchor('W').label('TEENSY 4.1\n\nPin 14 (A0)', 'center'))
        
    print("Engineering schematic successfully saved as 'pot_engineering_schematic.png'!")

if __name__ == '__main__':
    draw_engineering_schematic()
