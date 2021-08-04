/*
Abhishek Singh (191CS103)

CSCAN Disk Scheduling algorithm
*/
#include <bits/stdc++.h>
using namespace std;


class cscanalgo{
private:
    void CSCAN(int n,int arr[],int head,string direction,int disk_size);

public:
    void solve();
};

//function to facilitate CSCAN algorithm
void cscanalgo::CSCAN(int n,int arr[], int head, string direction,int disk_size)
{
	int total_count = 0;        //to count number of seek operations
	int distance, current;
	vector<int> left, right;   //to hold the tracks left and right to the initial R/W head position
	vector<int> sequence; //Sequence in which requests are executed
    sequence.push_back(head);
	//pushing the end values of disk
	if (direction == "left") left.push_back(0);
	else if (direction == "right") right.push_back(disk_size - 1);

	for (int i = 0; i < n; i++) {
		if (arr[i] < head) //if the value of current request is less than R/W head position
			left.push_back(arr[i]);
		if (arr[i] > head) //if the value of current request is less than R/W head position
			right.push_back(arr[i]);
	}

	//sorting the requests according to distance from current R/W head position
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	//if initial direction is left
	if(direction=="left")
    {
        //traversing to left
        for (int i = left.size() - 1; i >= 0; i--) {
            current = left[i];
            auto it=std::find(sequence.begin(), sequence.end(), current);
            if(it!=sequence.end()) continue;
            sequence.push_back(current);
            distance = abs(current - head);
            total_count += distance;
            head = current;
			}
        total_count+=(disk_size-1);
        head=disk_size-1; //traversing to (disk size-1)
        sequence.push_back(disk_size-1);
        //traversing to left
        for (int i = right.size()-1; i >=0 ; i--) {
                current = right[i];
                auto it=std::find(sequence.begin(), sequence.end(), current);
                if(it!=sequence.end()) continue;
                sequence.push_back(current);      //pushing the current request
				distance = abs(current - head);   //calculating absolute difference between current request and previous R/W head position
				total_count += distance;          //adding distance to total seek count

				head = current;                   //pointing head to current track
			}


    }
    //if initial direction is right
    else
    {
        //traversing to right
        for (int i = 0; i < right.size(); i++) {
            current = right[i];
            auto it=std::find(sequence.begin(), sequence.end(), current);
            if(it!=sequence.end()) continue;
            sequence.push_back(current);      //pushing the current request
            distance = abs(current - head);   //calculating absolute difference between current request and previous R/W head position
            total_count += distance;          //adding distance to total seek count
            head = current;                   //pointing head to current track
			}
        total_count+=(disk_size-1);
        head=0; //traversing to (disk size-1)
        sequence.push_back(0);
        //traversing to right
        for (int i = 0; i < left.size(); i++) {
            current = left[i];
            auto it=std::find(sequence.begin(), sequence.end(), current);
            if(it!=sequence.end()) continue;
            sequence.push_back(current);
            distance = abs(current - head);
            total_count += distance;
            head = current;
			}
    }

	//printing the final result

	cout << "\nThe sequence of seek operations is: \n" << endl;
    int i;
	for (i = 0; i < sequence.size()-1; i++) {
		cout << sequence[i] <<" ==> ";
	}
    cout << sequence[i];
	cout << "\n\nTotal number of seek operations = "<< total_count << endl;

}


//Driver Code
void cscanalgo::solve()
{
    int n,head,choice,disk_size;
	cout<<"Enter the number of pages: ";
	cin>>n;
	int arr[n];

    cout<<"\nEnter the total number of tracks in secondary memory : ";
    cin>>disk_size;
    cout<<"\n";
	for(int i=0;i<n;i++)
    {
        cout<<"Enter the track location of Page "<<i+1<<": ";
        cin>>arr[i];
        if(arr[i]>=disk_size || arr[i]<0)
        {
            cout<<"Invalid Track location entered\n\n";
            i--;
        }
    }
    while(1)
    {
      cout<<"\nEnter the initial position of Read/Write Head: ";
	  cin>> head;
	  if(head>=disk_size || head<0)
	  {
	      cout<<"Invalid Head location entered\n\n";
      }
      else break;
    }

    cout<<"\nSelect the initial direction of Read/Write Head: 1) Left 2) Right: ";
	cin>>choice;
	string direction="right";
    if(choice==1) direction="left";
	CSCAN(n,arr, head, direction,disk_size);
}
int main()
{
    cscanalgo s;
    s.solve();
}
