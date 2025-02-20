#include <TCPKernel.h>



int main(int argc,char *argv[])
{
    int port = 8800;
    if( argc >= 2 )
    {
        port = atoi(argv[1]);
    }
    TcpKernel * pKernel =  TcpKernel::GetInstance();


    pKernel->Open( port );
    cout << "port:" << port << endl ;
    // 事件循环 : 循环监听事件
    pKernel->EventLoop();

    pKernel->Close();

    return 0;
}
