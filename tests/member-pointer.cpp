struct Style {
  int direction;
  int flex;
  int getDirection() const { return direction; }
  void setDirection(int v) { direction = v; }
};

template <int Style::*Field, void (Style::*Setter)(int)>
void updateStyle(Style &s, int v) {
  if (s.*Field != v)
    (s.*Setter)(v);
}

template <typename M> int read(const Style &s, M member) { return s.*member; }

void fine(Style &s) {
  updateStyle<&Style::direction, &Style::setDirection>(s, 1);
  read(s, &Style::flex);
}

struct Table {
  int Style::*field;
  int (Style::*getter)() const;
};

int stored(const Style &s, void (Style::*setter)(int)) {
  int Style::*f = &Style::flex;
  static int (Style::*const getters[])() const = {&Style::getDirection};
  (void)setter;
  return s.*f + (s.*getters[0])();
}
