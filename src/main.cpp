#include "app.h"

int main(int argc, char *argv[]) {
    world_time::app time{};
    time.tell(argc, argv);
}
