#ifndef GHOSTSCRIPT_H
#define GHOSTSCRIPT_H

#include "externalSoftware.hpp"

class Ghostscript : public ExternalSoftware {
public:
  Ghostscript() {
    softwareName = "Ghostscript";
    softwareCommand = "gs";
  }
} ghostscript;
#endif // GHOSTSCRIPT_H
