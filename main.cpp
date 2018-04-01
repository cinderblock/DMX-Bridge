
#include <AVR++/IOpin.h>
#include <avr/io.h>

// #include "Clock.h"

using namespace AVR;

using R = Output<Ports::D, 5>; // OC0B 
using G = Output<Ports::D, 6>; // OC0A
using B = Output<Ports::D, 3>; // OC2B

// Read enable
using RE = Output<Ports::C, 5, true>;
using DE = Output<Ports::D, 2>;

using Tab = Output<Ports::B, 0>;

// u1 getSerialByte() {
//   while (!(UCSR0A & 0b10000000))
//     ;
//   return UDR0;
// }
// 
// u2 getSerialWord() {
//   u1 first = getSerialByte();
//   u1 second = getSerialByte();
// 
//   return first << 8 | second;
// }


int main() {
  RE::on();
  DE::off();

  UBRR0 = 4;
  
  // Set default
  UCSR0C = 0b00000110;
  
  // Set default
  UCSR0A = 0b00000000;
  
  // Enable Receiver
  UCSR0B = (1 << RXEN0);
  
  DDRD = 0b01101000;
  
  // R::off();
  // G::off();
  // B::on();
  
  PIND = 0b01000000;
  
  u1 last = 0xff;
 
  while (1) {
    
    while (!(UCSR0A & 0b10000000));
    u1 b = UDR0;
  
    if (last != 0 || b != 1) {
      last = b;
      continue;
    }
    
    while (!(UCSR0A & 0b10000000));
    u1 command = UDR0;
    
    
    while (!(UCSR0A & 0b10000000));
    
    if (command != ~UDR0) continue;
    
    while (!(UCSR0A & 0b10000000));
    
    if (UDR0 != 0xff) continue;
  
  
    R::set(command & 1);
    G::set(command & 2);
    B::set(command & 4);
  
  }
 
 return 0;  
}
