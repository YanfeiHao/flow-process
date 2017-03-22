#include "utility/ScopeTools.hpp"
#include <string.h>
#include "utility/UniquePtr.hpp"
#include <QDebug>
#include <stdlib.h>
#include <utility>
#include <QGraphicsScene>
#include <QApplication>

int main(int argc, char *argv[])
{
    auto ret = makeUnique<int[]> (100);
    return 0;
}
