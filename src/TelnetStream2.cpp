#include "TelnetStream2.h"

TelnetStream2Class::TelnetStream2Class(uint16_t port) :server(port) {
}

void TelnetStream2Class::begin() {
  server.begin();
  client = server.available();
}

void TelnetStream2Class::stop() {
  client.stop();
}

boolean TelnetStream2Class::disconnected() {
#ifdef ESP32
  if (!server)
    return true;
#else
  if (server.status() == CLOSED)
    return true;
#endif
  if (!client) {
    client = server.available();
  }
  if (client) {
    if (client.connected())
      return false;
    client.stop();
    client = server.available();
  }
  return true;
}

int TelnetStream2Class::read() {
  if (disconnected())
    return -1;
  return client.read();
}

int TelnetStream2Class::available() {
  if (disconnected())
    return 0;
  return client.available();
}

int TelnetStream2Class::peek() {
  if (disconnected())
    return -1;
  return client.peek();
}

size_t TelnetStream2Class::write(uint8_t val) {
  if (disconnected())
    return 1;
  return client.write(val);
}

void TelnetStream2Class::flush() {
  if (disconnected())
    return;
  client.flush();
}

TelnetStream2Class TelnetStream2(23);
