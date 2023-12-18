#include <bits/stdc++.h>
using namespace std;

bool contains(queue<int> q, int x)
{
    while (!q.empty())
    {
        if (q.front() == x)
        {
            return true;
        }
        q.pop();
    }

    return false;
}

class PageReplacement
{
private:
    int frames;

public:
    PageReplacement()
    {
        this->frames = 0;
    }

    PageReplacement(int n)
    {
        frames = n;
    }

    void fifo()
    {
        queue<int> pages;
        int faults = 0;
        int hits = 0;
        bool no_incr = false;
        while (true)
        {
            int n;
            cout << "Enter page or -1 to stop : ";
            cin >> n;

            if (n == -1)
            {
                break;
            }

            if (pages.size() < frames)
            {
                if (pages.empty())
                {
                    pages.push(n);
                    faults++;
                    no_incr = false;
                }
                else
                {
                    queue<int> dummy = pages;
                    if (contains(dummy, n))
                    {
                        cout << "Page found !" << endl;
                        hits++;
                        no_incr = true;
                    }
                    else
                    {
                        pages.push(n);
                        faults++;
                        no_incr = false;
                    }
                }
            }
            else if (pages.size() == frames)
            {
                queue<int> dummy = pages;
                if (contains(dummy, n))
                {
                    cout << "Page found !" << endl;
                    hits++;
                    no_incr = true;
                }
                else
                {
                    pages.pop();
                    pages.push(n);
                    faults++;
                    no_incr = false;
                }
            }

            queue<int> dummy = pages;
            cout << "Frames : ";
            while (!dummy.empty())
            {
                cout << dummy.front() << " ";
                dummy.pop();
            }

            if (no_incr)
            {
                cout << "Page hit" << endl;
            }
            else
            {
                cout << "Page faults : " << faults << endl;
            }
        }

        cout << "Total Page faults = " << faults << endl;
        cout << "Total Page hits = " << hits << endl;
    }

    // void optimal()
    // {
    //     vector<int> v1;
    //     map<int, int> mp;
    //     int size = 4;
    //     vector<int> v2;
    //     int n, page, faults = 0;
    //     cout << "Enter number of pages to be checked:" << endl;
    //     cin >> n;
    //     cout << "Enter the pages:" << endl;
    //     for (int i = 0; i < n; i++)
    //     {
    //         cin >> page;
    //         v1.push_back(page);
    //         mp[page]++;
    //     }
    //     for (int i = 0; i < v1.size(); i++)
    //     {
    //         if (v2.empty())
    //         {
    //             faults++;
    //             v2.push_back(v1[i]);
    //             continue;
    //         }
    //         else if (v2.size() < size)
    //         {
    //             int label = 0;
    //             for (int j = 0; j < v2.size(); j++)
    //             {
    //                 if (v2[j] == v1[i])
    //                 {
    //                     label = 1;
    //                     cout << "Page found!" << endl;
    //                     break;
    //                 }
    //             }
    //             if (label == 0)
    //             {
    //                 v2.push_back(v1[i]);
    //                 faults++;
    //             }
    //         }
    //         else if (v2.size() == size)
    //         {
    //             int min = INT_MAX, minInd = -1;
    //             int label = 0;
    //             for (int j = 0; j < v2.size(); j++)
    //             {
    //                 if (v2[j] == v1[i])
    //                 {
    //                     label = 1;
    //                     cout << "Page found!" << endl;
    //                     break;
    //                 }
    //             }
    //             if (!label)
    //             {
    //                 faults++;
    //                 for (int j = 0; j < v2.size(); j++)
    //                 {
    //                     if (min > mp[v2[j]])
    //                     {
    //                         min = mp[v2[j]];
    //                         minInd = j;
    //                     }
    //                 }
    //                 v2[minInd] = v1[i];
    //             }
    //         }
    //     }
    //     cout << "No of faults:" << faults;
    // }

    int optimalPageReplacement(int capacity, vector<int> pages)
    {
        int pageFaults = 0;
        unordered_map<int, int> pageIndices; // Stores the index of the next occurrence of each page

        vector<int> frames(capacity, -1);

        for (int i = 0; i < pages.size(); ++i)
        {
            int page = pages[i];

            // Check if page is already in frames
            if (pageIndices.find(page) != pageIndices.end())
            {
                frames[pageIndices[page]] = i;
            }
            else
            {
                int maxIndex = 0;
                int nextPage = frames[0];

                for (int j = 0; j < capacity; ++j)
                {
                    if (frames[j] == -1)
                    {
                        maxIndex = j;
                        break;
                    }

                    if (frames[j] > frames[maxIndex])
                    {
                        maxIndex = j;
                        nextPage = frames[j];
                    }
                }

                frames[maxIndex] = page;
                pageIndices[page] = i;
                pageIndices[nextPage] = -1;
                pageFaults++;
            }
        }
        return pageFaults;
    }

    void LRU()
    {
        list<int> lruList;
        int faults = 0;
        int hits = 0;
        int n;
        bool no_incr = false;
        while (true)
        {
            cin >> n;
            if (n == -1)
            {
                break;
            }

            auto it = find(lruList.begin(), lruList.end(), n);

            if (it != lruList.end())
            {
                hits++;
                lruList.erase(it);
                lruList.push_back(n);
                no_incr = true;
            }
            else
            {
                faults++;
                lruList.push_back(n);
                no_incr = false;

                if (lruList.size() > frames)
                {
                    lruList.pop_front();
                }
            }

            cout << "Frames : ";
            for (auto it = lruList.begin(); it != lruList.end(); it++)
            {
                cout << *it << " ";
            }
            cout << endl;

            if (no_incr)
                cout << "Page hit" << endl;
            else
                cout << "Page fault : " << faults << endl;
        }

        cout << "Total page faults: " << faults << endl;
        cout << "Total page hits: " << hits << endl;
    }
};

int main()
{
    int frames;
    cout << "Enter number of page frames : ";
    cin >> frames;
    PageReplacement p(frames);
    // p.LRU();
    int numPages;
    cout << "Enter the number of pages: ";
    cin >> numPages;

    cout << "Enter the page reference string: ";
    vector<int> pages(numPages);
    for (int i = 0; i < numPages; ++i)
    {
        cin >> pages[i];
    }

    cout << p.optimalPageReplacement(frames, pages);

    return 0;
}
