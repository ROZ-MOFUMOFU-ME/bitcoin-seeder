#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "bitcoin.h"
#include "protocol.h"

using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <ip:port>\n", argv[0]);
    return 1;
  }
  
  const char* ipport = argv[1];
  char ip[256];
  int port = 7586;
  
  if (strchr(ipport, ':')) {
    sscanf(ipport, "%[^:]:%d", ip, &port);
  } else {
    strcpy(ip, ipport);
  }
  
  CService cip(ip, port, true);
  
  printf("Testing node %s:%d\n", ip, port);
  
  int ban = 0;
  int clientV = 0;
  std::string clientSV;
  int blocks = 0;
  uint64_t services = 0;
  
  bool ret = TestNode(cip, ban, clientV, clientSV, blocks, nullptr, services);
  
  printf("Result: %s\n", ret ? "GOOD" : "BAD");
  printf("Ban: %d\n", ban);
  printf("Client version: %d\n", clientV);
  printf("Client subversion: %s\n", clientSV.c_str());
  printf("Blocks: %d\n", blocks);
  printf("Services: %llu\n", (unsigned long long)services);
  
  return 0;
}