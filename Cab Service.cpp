//shortest job first
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
struct passenger
{
    int destination;
    int num;
    int location;
    bool inside;
    int diff;
};
void wait(int&s)
{
    if(s==0)
    {
        cout<<"DEADLOCK\n";
      return;
    }
    else
        s--;
}
void signal(int&s)
{
    s++;
}
void signal(bool &x)
{
    x=true;
}
void wait(bool &x)
{
    if(x==false)
    {
        cout<<"DEADLOCK\n\n";
        return;
    }
    else
    {
        x=false;
    }
}
bool comp(passenger a,passenger b)
{
    if(a.diff<b.diff)
        return true;
    else
        return false;
}
int semaphore;
bool mutex=false,c=true;
int main()
{
    vector<passenger>check;
  cout<<"                                CAB SERVICE:       ON\n";
  int capacity;
  cout<<"\n\n\nINPUT THE CAPACITY OF THE CAB\n";
  cin>>capacity;
  cout<<"INPUT THE NUMBER OF  PASSENGERS\n";
  int pass;
  cin>>pass;
passenger  passengers[pass];
  int n=1;
  int maxi=-1;
  for(int i=0;i<pass;i++)
  {  passengers[i].num=i+1;
      cout<<"ENTER THE LOCATION OF PASSENGER NUMBER "<<i+1<<"=";
      cin>>passengers[i].location;
    cout<<"ENTER THE destination OF THE PASSENGER NUMBER "<<i+1<<"=";
      cin>>passengers[i].destination;
       if(maxi<passengers[i].destination)
       {
           maxi=passengers[i].destination;
       }
     passengers[i].diff = passengers[i].destination - passengers[i].location;
     passengers[i].inside=false;
  }
   while(1)//infinite : bankers
   {
       int count=0;
       for(int j=0;j<pass;j++)
       {
           if(passengers[j].diff==0)
            count++;
       }
       if(count==pass)
       {
           cout<<"ALL PASSENGERS HAVE REACHED THEIR DESTINATION\n";
           break;
       }

       cout<<" CAB WILL BE TRAVELLING FOR 50 KMS\n";
    for(int i=0;i<maxi;i++)
    {  getchar();// or Sleep(2000);
         cout<<"\n Car Travelled ="<<i<<"KM"<<endl;
        if(mutex)//critical section 1
            {
                for(int j=0;j<pass;j++)
                {
                    if(passengers[j].inside)
                    {
                        passengers[j].diff = passengers[j].destination-i;
                    }
                }

               for(int j=0;j<pass;j++)
              {
                  if(passengers[j].inside)
                  {
                      if(passengers[j].destination==i)
                      {
                          passengers[j].inside=false;
                          wait(semaphore);
                          if(semaphore==0)
                            wait(mutex);
                      }
                  }
              }
              cout<<"NUMBER OF PASSENGERS INSIDE THE CAB = "<<semaphore<<endl;
               for(int j=0;j<pass;j++)
         {
            if(passengers[j].inside)
            {
                cout<<"passenger number="<<passengers[j].num<<endl;
                cout<<"passenger destination = "<<passengers[j].destination<<endl;
                cout<<"passenger diff = " << passengers[j].diff<<endl<<endl<<endl;
            }
            cout<<endl;
         }

    }
        if(semaphore<capacity)
        {
                 if(c)
                 {
                      cout<<"       CAB SERVICE:       ON\n";
                      c=false;
                 }
            for(int j=0;j<pass;j++)//critical section 2
            {
                if(!passengers[j].inside&&passengers[j].diff!=0)
                {
                    if(passengers[j].location==i)
                    {
                        check.push_back(passengers[j]);
                    }
                }
            }
            if(check.size())
            {
                sort(check.begin(),check.end(),comp);
               for(int j=0;j<check.size();j++)
               {
                     if(semaphore<capacity)
                     {

                         passengers[check[j].num-1].inside=true;
                           cout<<" passenger number="<<passengers[check[j].num-1].num<<" picked " << endl;
                           cout<<" passenger destination = "<<passengers[check[j].num-1].destination<<endl;
                           cout<<" passenger diff = " << passengers[check[j].num-1].diff<<endl<<endl<<endl;

                         signal(semaphore);
                         signal(mutex);


                     }
               }
               while(check.size())
                check.pop_back();
            }
            if(semaphore==capacity)
                 {
                     cout<<"CAB SERVICE:       OFF\n";
                   c = true;
                 }
        }
        else
        {
            for(int j=0;j<pass;j++)
            {
                if(!passengers[j].inside)
                {
                   if(passengers[j].location==i)
                   {
                       for(int k=0;k<pass;k++)
                       {
                         if(passengers[k].inside)
                         {
                             passengers[k].diff=passengers[k].destination-i;

                         }
                       }
                       //pre-emption
                       int max=-1,ind;
                       for(int k=0;k<pass;k++)
                       {
                         if(passengers[k].inside)
                         {
                             if(passengers[k].diff>max)
                             {
                                 max=passengers[k].diff;
                                ind=passengers[k].num-1;
                             }

                         }

                      }
                      //pre-emption condition
                      if(max>passengers[j].diff)
                      {
                         passengers[ind].inside = false;
                         passengers[ind].location=i;
                         passengers[j].inside = true;
                      }


                   }
                }
            }

        }
        cout<<"\n\nNUMBER OF PASSENGER INSIDE THE CAB : "<<semaphore<<endl<<endl;
        for(int j=0;j<pass;j++)
        {
            if(passengers[j].inside)
            {
                cout<<"passenger number="<<passengers[j].num<<endl;
                cout<<"passenger destination = "<<passengers[j].destination<<endl;
                cout<<"passenger diff = " << passengers[j].diff<<endl<<endl<<endl;
            }
            cout<<endl;
        }


    }

   }
}


