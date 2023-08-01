#include "Engine.h"

int main(void)
{
    ugly::engine::get_instance()->run(new ugly::application());

    return 0;
}