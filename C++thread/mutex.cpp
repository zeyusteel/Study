#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

/*这种情况保证了钱包里的钱不会出现少于5000的情况，因为addMoney()中的互斥锁确保了只有在一个线程修改完成money后，
另一个线程才能对其进行修改，但是，如果我们忘记在函数结束后对锁进行释放会怎么样？
这种情况下，一个线程将退出而不释放锁，其他线程将保持等待，为了避免这种情况，我们应当使用std::lock_guard。 

std::lock_guard是一个template class，它为mutex实现RALL，它将mutex包裹在其对象内，并将附加的mutex锁定在其构造函数中，
当其析构函数被调用时，它将释放互斥体。
*/
class WalletLockGuard
{
    int mMoney;
    std::mutex mutex;

public:
    WalletLockGuard() :mMoney(0){}
    int getMoney()   {     return mMoney; }
    void addMoney(int money)
    {
        std::lock_guard<std::mutex> lockGuard(mutex);

        for(int i = 0; i < money; ++i)
        {
            mMoney++;
        }
    }
};

class Wallet
{
    int mMoney;
    std::mutex mutex;

public:
    Wallet() :mMoney(0){}
    int getMoney()   {     return mMoney; }
    void addMoney(int money)
    {
        mutex.lock();
        for(int i = 0; i < money; ++i)
        {
            mMoney++;
        }
        mutex.unlock();
    }
};

int testMultithreadedWallet()
{
    Wallet walletObject;
    std::vector<std::thread> threads;
    for(int i = 0; i < 5; ++i){
        threads.push_back(std::thread(&Wallet::addMoney, &walletObject, 1000));
    }
    for(int i = 0; i < threads.size() ; i++)
    {
        threads.at(i).join();
    }
    return walletObject.getMoney();
}

int main()
{
    int val = 0;
    for(int k = 0; k < 1000; k++)
    {
        if((val = testMultithreadedWallet()) != 5000)
        {
            std::cout << "Error at count = "<<k<<"  Money in Wallet = "<<val << std::endl;
            //break;
        }
    }
    return 0;
}