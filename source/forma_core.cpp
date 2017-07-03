#include "forma_core.hpp"
#include <pessum/pessum.hpp>
#include <string>

void forma::InitForma() {
  pessum::Log(pessum::INFO, "Forma Version: %i.%i.%i", "forma::InitForma",
              FORMA_VERSION_MAJOR, FORMA_VERSION_MINOR, FORMA_VERSION_PATCH);
}

void forma::TermForma() {}

void forma::GetVersion(int &major, int &minor, int &patch) {
  major = FORMA_VERSION_MAJOR;
  minor = FORMA_VERSION_MINOR;
  patch = FORMA_VERSION_PATCH;
}
