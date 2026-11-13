#include "Collection.h"
#include "UI.h"

int main()
{
    Collection collection;
    UI ui{collection};
    ui.run();

    return 0;
}