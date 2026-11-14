# ARINC 429 Decoder

A C++ program that receives ARINC 429 words over UDP and decodes them into readable flight information. ARINC 429 is the data bus standard used by most commercial aircraft avionics.

The program output and source comments are in French.

## Demo

https://github.com/chris-jeune/Decoder-ARINCA-429/assets/145855247/9653d571-8a7c-4cf4-9428-e2af4576afbc

## What it does

- Listens on a UDP port (55001 by default) for 32-bit ARINC 429 words sent by a data concentrator.
- Extracts the label from each word and displays it in octal, as the standard specifies.
- Checks the parity of each word and flags corrupted ones.
- Decodes the data field as BCD or BNR depending on the label.
- Prints one line per new word: the raw value, whether it is corrupted, and the decoded data.

Decoded information includes the flight time, flight date, altitude, and the departure and arrival airports.

## Project layout

| File | Purpose |
|---|---|
| `main.cpp` | Application mode: receives words and prints them |
| `test.cpp` | Test mode: exercises the utility and decoding functions |
| `a429.cpp`, `a429.h` | ARINC 429 word decoding and display |
| `port_udp.cpp`, `port_udp.h` | UDP socket setup, receive and transmit (Winsock) |
| `utilitaire.cpp`, `utilitaire.h` | Helpers: octal conversion, bit counting, time and bit display |
| `configuration.h` | Build mode, UDP port and parity settings |

## Build and run

The UDP layer uses Winsock, so the program builds on Windows.

1. Clone the repository.
2. In `configuration.h`, define either `APPLICATION` (the decoder) or `TEST` (the test program).
3. Compile all `.cpp` files with a C++ compiler, for example in Visual Studio.
4. In application mode, start a data concentrator that sends ARINC 429 words to UDP port 55001, then run the decoder.
