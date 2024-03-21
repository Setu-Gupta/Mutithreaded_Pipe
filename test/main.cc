#include <iostream>
#include <pipe.h>
#include <thread>

#define PIPE_SIZE 3

void produce(multipipe::Pipe<int, PIPE_SIZE>& p)
{
        for(int i = 0; i < 10; i++) p.transmit_data(std::forward<int>(i));
        p.finish_transmission();
}

void consume(multipipe::Pipe<int, PIPE_SIZE>& p)
{
        while(true)
        {
                std::optional<int> data = p.receive_data();
                if(!data.has_value())
                        break;
                std::cout << "Got " << data.value();
        }
}

int main()
{
        multipipe::Pipe<int, PIPE_SIZE> p;
        std::thread                     producer(produce, std::ref(p));
        std::thread                     consumer(consume, std::ref(p));
        producer.join();
        consumer.join();
        return 0;
}
