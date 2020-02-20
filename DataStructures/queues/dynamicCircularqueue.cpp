#include <bits/stdc++.h>
using namespace std;

class Queue
{
private:
    int *arr;
    int cnt; //number of elements in the queue
    int cap; //max size of the queue
    int front, rear;

    void resize()
    {
        int size = cap;
        cap *= 2;
        int *newarr = new int[cap];
        for (int i = front; i < size; i++)
        {
            newarr[i + size] = arr[i];
        }

        if (front > rear)
        {
            for (int i = 0; i <= rear; i++)
            {
                newarr[i] = arr[i];
            }
        }
        else
        {
            rear = rear + size;
        }
        front = front + size;
        delete (arr);
        arr = newarr;
    }

public:
    Queue(int cap)
    {
        this->cap = cap;
        arr = new int[cap];
        cnt = 0;
        front = rear = -1;
    }

    int getcount()
    {
        return cnt;
    }

    int getsize()
    {
        return cap;
    }

    bool full()
    {
        return cnt == cap;
    }

    bool empty()
    {
        return cnt == 0;
    }

    void push(int data)
    {
        if (full())
            resize();
        cnt++;
        rear = (rear + 1) % cap;
        arr[rear] = data;
        if (front == -1)
            front = rear;
    }

    int pop()
    {
        if (empty())
            return INT_MIN;
        int data = arr[front];
        front = (front + 1) % cap;
        --cnt;
        return data;
    }
};

int main()
{
    Queue q(5);
    for (int i = 1; i <= 10; i++)
    {
        q.push(i);
    }

    q.push(120);

    while (!q.empty())
    {
        cout << q.pop() << " ";
    }
    cout << "\n";
    return 0;
}