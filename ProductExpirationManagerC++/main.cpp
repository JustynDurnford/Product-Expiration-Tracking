// ProductExpirationManagerC++
// main.cpp
// Created on Feb 03 2026 by Justyn Durnford
// Last modified on Nov 01 2026 by Justyn Durnford
// Main file.

#include "Config.h"
#include "Manager.h"

int main()
{
    Config config;

    Manager manager(config);
    manager.start();
    return 0;
}