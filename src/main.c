#include "callback.h"

static void
MyRegisterCallBack (DNSServiceRef service,
                    DNSServiceFlags flags,
                    DNSServiceErrorType errorCode,
                    const char * name,
                    const char * type,
                    const char * domain,
                    void * context)
{
    if (errorCode != kDNSServiceErr_NoError)
        fprintf (stderr, "MyRegisterCallBack return %d\n", errorCode);
    else
        printf ("%-15s %s.%s%s\n", "REGISTER", name, type, domain);
}

static DNSServiceErrorType
MyDNSServiceRegister ()
{
    DNSServiceErrorType error;
    DNSServiceRef serviceRef;

    error = DNSServiceRegister (&serviceRef, 0, 0, "Not a real page",
            "_rps._tcp", "", NULL, htons (PORT_NUM), 0, NULL,
            MyRegisterCallBack, NULL);

    if (error == 0)
    {
        HandleEvents (serviceRef);
        DNSServiceRefDeallocate (serviceRef);
    }

    return error;
}

int main (int argc, const char * argv[])
{
    DNSServiceErrorType error = MyDNSServiceRegister ();
    fprintf (stderr, "DNSServiceDiscovery returned %d\n", error);
    return 0;
}
