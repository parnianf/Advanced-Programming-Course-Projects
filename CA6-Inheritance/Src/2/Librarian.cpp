#include "Librarian.hpp"
using namespace std;
#define QUIET "Quiet!"
Librarian::Librarian(Channel *channel_)
{
    channel = channel_;
    messageNumbers = 1;
}

void Librarian::update(string message)
{
    if (messageNumbers % 5 == 0)
    {
        messageNumbers++;
        channel->setMessage(QUIET);
    }
    else
    {
        messageNumbers++;
    }
}
