#include "Utils.h"

#include <interface/Alert.h>
#include <support/Autolock.h>
#include <stdio.h>

void Error(const char* message, status_t code)
{
    BAlert* alert;
    char buff[256];
    sprintf(buff, "%s : %d", message, code);
    alert = new BAlert("about box", buff, "OK");
    alert->Go(nullptr);
}

// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
