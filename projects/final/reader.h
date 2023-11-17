#ifndef READER_H
#define READER_H

class Reader {
private:
  // value semantics are prohibited
  Reader(const Reader &);
  Reader &operator=(const Reader &);

public:
  Reader();
  ~Reader();

  // read plot description from given istream;
  // throw a PlotException if any errors are found
  void read_input(std::istream &in, Plot &plot);
};

#endif // READER_H
