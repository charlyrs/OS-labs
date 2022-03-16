
#include <iostream>
#include "buffered_chanel.h"


int main()
{
    BufferedChannel<int> bc(5);
    int res4, res1, res2, res3;
   
    std::thread t1([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        bc.Send(2);
        bc.Send(4); 
        bc.Send(6);
        });
     std::thread t3([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        bc.Send(0);
        res1 = bc.Recv().first;
        res2 = bc.Recv().first;
        });
    std::thread t2([&]() {
        res3 = bc.Recv().first;
        res4 = bc.Recv().first;
        });
   
    t1.join();
    t2.join();
    t3.join();
    std::cout << res1 << "  " << res2 << "  " << res3 << "  " << res4 << "  ";
    
}

