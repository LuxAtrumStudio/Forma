#include "forma_core.hpp"
#include "log/log.hpp"

int main(int argc, char const* argv[]) {
  forma::InitForma();
  forma::TermForma();
  forma::log::SaveLog("out.log");
  return 0;
}
