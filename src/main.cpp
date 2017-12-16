#include "Interface.h"
#include "FileSystem.h"

int main()
{
    FileSystem fs ;
    fs.setFileNumber(0) ;
    fs.run() ;
    
    return 0;
}

