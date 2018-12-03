class Star {
  public:

    int index = 0;
    int width = 0;
    int hue = 0;
    int startTime = 0;

    Star(int _index, int _width, int _hue) {
      index = _index - 1;
      width = _width;
      hue = _hue;
    }

    void setLeds() {
      int half = width / 2;
      int unit = 250 / half;
      for (int led = 0; led < half; led++) {
        int ledindex = led + index;
        leds[led] = CHSV(hue, 200, unit * led);
      }
      for (int led = 0; led < half; led++) {
        int ledindex = led + index + half;
        leds[led] = CHSV(hue, 200, 250 - (unit * led));
      }
    }
}
