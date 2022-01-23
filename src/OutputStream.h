#pragma once

class OutputStream {
  
public:
  virtual ~OutputStream() { close(); }
  virtual int writeByte(int b); // write a single byte, return -ve for error
  virtual int writeWord(int w); // write 2 bytes LSB first, return  -ve for error
  virtual int write(unsigned char* buffer, const unsigned int length); // return -ve for error
  virtual void close() {};
  virtual bool closed() { return true; };
};
