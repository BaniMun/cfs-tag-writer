## v1.3.0

- The spool moves: it winds up filament while a tag is being written, turns
  while reading and erasing, turns slowly in the main menu, and makes a short
  turn in the color picker after each move (in the direction you scroll).
- The spool hub now has three spokes, which is what shows it turning.

## v1.2.0

- New look: the app's main screens are drawn by the app itself instead of
  plain text lists.
- Main menu: spool logo on the left, list with icons on the right.
- Color picker on one screen: Left/Right switch family (shade families, then
  Basic colors, then Custom hex), Up/Down move through shades, OK picks. The
  spool fills with a dither pattern showing how light or dark the color is.
- Spool card for the write confirm screen and read results: material, brand,
  color name, weight and length, serial.
- Reading, writing and erasing show a spool with animated NFC waves; results
  show a check or a cross. Failed reads, writes and erases offer Retry
  instead of dropping back to the menu.

## v1.1.0

- Color picker by family: pick a hue family (Reds, Greens, Whites & Grays, ...),
  then a named shade, listed light -> dark (240 shades, generated from
  meodai/color-names by scripts/gen_color_shades.py).
- Classic palette moved under "Basic colors"; "Custom hex..." starts from the
  picked shade, so it can be fine-tuned.
- Confirm screen shows the nearest color name next to the hex.

## v1.0.1

- Correct the built-in Generic PET catalog temperature range from 210–230 °C
  to 250–270 °C to match Creality's material database.

## v1.0

- Initial release
