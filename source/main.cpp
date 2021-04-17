#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3 || strncmp(argv[1], "-h", 2) == 0)
    {
        cerr << "Usage: " << argv[0] << " [options] <input> <output>" << endl
             << "Supported inputs: Radiance spheremap (.hdr)" << endl
             << "Supported outputs: Direct Draw Surface cubemap (.dds)" << endl
             << "Supported options: none yet" << endl;

        return 1;
    }

    return 0;
}
